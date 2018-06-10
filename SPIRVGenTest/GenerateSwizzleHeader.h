//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_GENERATESWIZZLEHEADER_H
#define SPEAR_GENERATESWIZZLEHEADER_H

#include <fstream>
#include <string>

void GenerateSwizzleHeader()
{
	std::string ups[4] = { "X", "Y", "Z", "W" };
	char lows[2][4] = { { 'x', 'y', 'z', 'w' },{ 'r', 'g', 'b', 'a' } };

	std::ofstream out("SPIRVVectorComponentAccess.h");

	if (out.is_open())
	{
		out << "#ifndef SPEAR_SPIRVVECTORCOMPONENTACCESS_H" << std::endl;
		out << "#define SPEAR_SPIRVVECTORCOMPONENTACCESS_H" << std::endl;

		std::string sTplArgs;
		std::string sExtract;
		std::string sExtractType;
		std::string sInsert;
		std::string sInsertConst;
		std::string sInsertValue;
		std::string sFuncName;

		auto GetSet = [&]() {
			// getter
			out << sExtractType << " "
				<< sFuncName << "() const { return " << sExtract << "(); } " << std::endl;

			// setter var
			out << "template <spv::StorageClass C1> void "
				<< sFuncName << "(" + sInsertValue + " _var) const { " + sInsert + "(_var);}" << std::endl;

			// setter const
			out << "void "
				<< sFuncName << "(const " + sInsertConst + "& _var) const { " + sInsert + "(var_t<"+ sInsertConst +", Assemble, spv::StorageClassFunction>(_var));}" << std::endl;
		};

		for (uint32_t x = 0; x < 4; ++x)
		{
			sTplArgs = "1, " + std::to_string(x);
			sExtract =	"ExtractComponent<" + sTplArgs + ">";
			sInsert =	"InsertComponent<" + sTplArgs + ">";
			sInsertConst = "vec_type_t<base_type_t<T>, 1>";
			sInsertValue = "const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>&";
			sFuncName = ups[x];
			sExtractType = "TExtractType<1>";

			GetSet();
	
			// property
			for (uint32_t l = 0; l < 2; ++l)
			{
				out << "__declspec(property(get = " << sFuncName << ", put = " << sFuncName <<
					")) " << sExtractType << " " << lows[l][x] << ";" << std::endl;
			}

			for (uint32_t y = 0; y < 4; ++y)
			{
				sTplArgs = "2, " + std::to_string(x) + ", " + std::to_string(y);
				sExtract = "ExtractComponent<" + sTplArgs + ">";
				sInsert = "InsertComponent<" + sTplArgs + ">";
				sInsertConst = "vec_type_t<base_type_t<T>, 2>";
				sInsertValue = "const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>&";
				sFuncName = ups[x] + ups[y];
				sExtractType = "TExtractType<2>";

				GetSet();

				// property
				for (uint32_t l = 0; l < 2; ++l)
				{
					out << "__declspec(property(get = " << sFuncName << ", put = " << sFuncName <<
						")) " << sExtractType << " " << lows[l][x] << lows[l][y] << ";" << std::endl;
				}

				for (uint32_t z = 0; z < 4; ++z)
				{
					sTplArgs = "3, " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
					sExtract = "ExtractComponent<" + sTplArgs + ">";
					sInsert = "InsertComponent<" + sTplArgs + ">";
					sInsertConst = "vec_type_t<base_type_t<T>, 3>";
					sInsertValue = "const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>&";
					sFuncName = ups[x] + ups[y] + ups[z];
					sExtractType = "TExtractType<3>";

					GetSet();

					// property
					for (uint32_t l = 0; l < 2; ++l)
					{
						out << "__declspec(property(get = " << sFuncName << ", put = " << sFuncName <<
							")) " << sExtractType << " " << lows[l][x] << lows[l][y] << lows[l][z] << ";" << std::endl;
					}

					for (uint32_t w = 0; w < 4; ++w)
					{
						sTplArgs = "3, " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w);
						sExtract = "ExtractComponent<" + sTplArgs + ">";
						sInsert = "InsertComponent<" + sTplArgs + ">";
						sInsertConst = "vec_type_t<base_type_t<T>, 4>";
						sInsertValue = "const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>&";
						sFuncName = ups[x] + ups[y] + ups[z] + ups[w];
						sExtractType = "TExtractType<4>";

						GetSet();

						// property
						for (uint32_t l = 0; l < 2; ++l)
						{
							out << "__declspec(property(get = " << sFuncName << ", put = " << sFuncName <<
								")) " << sExtractType << " " << lows[l][x] << lows[l][y] << lows[l][z] << lows[l][w] << ";" << std::endl;
						}
					}
				}
			}
		}

		out << "#endif // !SPEAR_SPIRVVECTORCOMPONENTACCESS_H" << std::endl;
	}

	out.close();
}

#endif // !SPEAR_GENERATESWIZZLEHEADER_H
