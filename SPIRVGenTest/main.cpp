//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#define ExprCaptureRule &

#include "SPIRVModule.h"
//#include "SPIRVInlineAssembler.h"
//#include "GenerateSwizzleHeader.h"
//#include "ExampleProg.h"
//#include "..\SPIRVShaderFactory\CSGExampleShader.h"
#include "DeferredLightingExample.h"
#include "StopWatch.h"

using namespace Spear;

uint32_t uPerm = 0u;

template <uint32_t pl, uint32_t sl>
uint32_t compile(const TDLPerm& _Perm, const std::string& _sOutputPath = {}, const bool _vValidate = false)
{

	SPIRVModule Shader = GlobalAssembler.AssembleSimple<DeferredLighting<1u, pl, sl>>(true, _Perm);
	const uint32_t uWordCount = static_cast<uint32_t>(Shader.GetCode().size());
	const uint32_t uInstrCount = Shader.GetNumberOfOperations();
	HLOG("P %u PL %u SL %u [%u] Instr %u Words %u", _Perm.GetBase(), pl, sl, ++uPerm, uInstrCount, uWordCount);

	if (_sOutputPath.empty() == false)
	{
		Shader.Save(_sOutputPath);

		if (_vValidate)
		{
			system(("spirv-dis " + _sOutputPath).c_str());
			system(("spirv-val " + _sOutputPath).c_str());
		}
	}

	return uWordCount;
}

inline uint32_t AssembleTest()
{
	uint32_t uWordCount = 0u;

	for (uint32_t p = 0; p < 4; ++p)
	{
		//compile<1u, 1u>(0u);

		uWordCount += compile<1u, 1u>(TDLPerm(p));
		uWordCount += compile<16u, 1u>(TDLPerm(p));
		uWordCount += compile<32u, 1u>(TDLPerm(p));
		uWordCount += compile<48u, 1u>(TDLPerm(p));

		uWordCount += compile<1u, 16u>(TDLPerm(p));
		uWordCount += compile<1u, 32u>(TDLPerm(p));
		uWordCount += compile<1u, 48u>(TDLPerm(p));

		uWordCount += compile<16u, 16u>(TDLPerm(p));
		uWordCount += compile<16u, 32u>(TDLPerm(p));
		uWordCount += compile<16u, 48u>(TDLPerm(p));

		uWordCount += compile<32u, 16u>(TDLPerm(p));
		uWordCount += compile<32u, 32u>(TDLPerm(p));
		uWordCount += compile<32u, 48u>(TDLPerm(p));

		uWordCount += compile<48u, 16u>(TDLPerm(p));
		uWordCount += compile<48u, 32u>(TDLPerm(p));
		uWordCount += compile<48u, 48u>(TDLPerm(p));
	}

	return uWordCount;
}

int main(int argc, char* argv[])
{
	//GenerateSwizzleHeader();

	//CSGExampleShader<false> prog;
	//prog.kFragCoord.xy = { 800.f, 450.f };
	//prog();

	//auto col = prog.OutputColor.Value;

	//return 0;

	//GlobalAssembler.AssembleSimple<ExampleProg<true>>().Save("test.spv");
	//system("spirv-dis test.spv");
	//system("spirv-val test.spv");
	//system("pause");

	//return 0;

	OptimizationSettings Settings{};
	//Settings.kPasses = kOptimizationPassFlag_AllPerformance;
	//Settings.kPasses = kOptimizationPassFlag_AllSize;
	//Settings.kPasses = kOptimizationPassFlag_All;

	GlobalAssembler.ConfigureOptimization(Settings);
	GlobalAssembler.RemoveUnusedOperations(false); // Disable own implementation

	if (false)
	{
		TDLPerm Perm = {};
		compile<1u, 1u>(Perm, "unopt.spv", true);

		GlobalAssembler.RemoveUnusedOperations(true);
		compile<1u, 1u>(Perm, "rem.spv", true);
		GlobalAssembler.RemoveUnusedOperations(false);

		Settings.kPasses = kOptimizationPassFlag_AllPerformance;
		GlobalAssembler.ConfigureOptimization(Settings);

		compile<1u, 1u>(Perm, "opt.spv", true);
	}
	else
	{
		if (false) // word count teste
		{
			hlx::Logger::Instance()->WriteToStream(&std::wcout);

			GlobalAssembler.ConfigureOptimization({}); // no opt
			GlobalAssembler.RemoveUnusedOperations(false); // Disable own implementation

			HLOG("UNOPTIMIZED:");
			const uint32_t uUnOptWords = AssembleTest();

			GlobalAssembler.RemoveUnusedOperations(true); 

			HLOG("REMOVED UNREFERENCED OPERATIONS:");
			const uint32_t uUnRefWords = AssembleTest();

			Settings.kPasses = kOptimizationPassFlag_AllPerformance;
			GlobalAssembler.ConfigureOptimization(Settings);
			GlobalAssembler.RemoveUnusedOperations(false);

			HLOG("SPIRV-OPT ALL PERFORMANCE:");
			const uint32_t uOptWords = AssembleTest();

			GlobalAssembler.RemoveUnusedOperations(true);

			HLOG("REMOVED UNREFERENCED + SPIRV-OPT ALL PERFORMANCE:");
			const uint32_t uOptUnRefWords = AssembleTest();

			const auto percent = [](uint32_t uCount, uint32_t uTotal) -> float
			{
				return ((float)uCount / (float)uTotal) * 100.f;
			};

			const auto factor = [](uint32_t uCount, uint32_t uTotal) -> float
			{
				return ((float)uTotal / (float)uCount);
			};

			HLOG("\nTotal instruction word count (4byte integers in stream):");
			HLOG("Unoptimized:\t\t%u %.2f%% %.3fx", uUnOptWords, percent(uUnOptWords, uUnOptWords), factor(uUnOptWords, uUnOptWords));
			HLOG("RemovedUnRef:\t%u %.2f%% %.3fx", uUnRefWords, percent(uUnRefWords, uUnOptWords), factor(uUnRefWords, uUnOptWords));
			HLOG("Optimized:\t\t%u %.2f%% %.3fx", uOptWords, percent(uOptWords, uUnOptWords), factor(uOptWords, uUnOptWords));
			HLOG("UnRefOptimized:\t%u %.2f%% %.3fx", uOptUnRefWords, percent(uOptUnRefWords, uUnOptWords), factor(uOptUnRefWords, uUnOptWords));
		}
		else // assemble time test
		{
			// warmup
			AssembleTest();

			hlx::Logger::Instance()->SetLogLevel(hlx::kMessageType_Fatal);

			hlx::StopWatch<> total;
			constexpr uint32_t uSampleCount = 10u;
			for (uint32_t i = 0; i < uSampleCount; i++)
			{
				hlx::StopWatch<> tone;

				AssembleTest();

				std::cout << tone.Elapsed() << "s" << std::endl;
			}

			const auto fElapsed = total.Elapsed();
			const float fAvg = fElapsed / (float)uSampleCount;
			std::cout << "Samples " << uSampleCount << " elapsed " << fElapsed << " avg " << fAvg << std::endl;
		}
	}

	//system("pause");

	return 0;
}