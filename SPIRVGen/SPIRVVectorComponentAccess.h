//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SPIRVVECTORCOMPONENTACCESS_H
#define SPEAR_SPIRVVECTORCOMPONENTACCESS_H
TExtractType<1> X() const { return ExtractComponent<1, 0>(); } 
template <spv::StorageClass C1> void X(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) const { InsertComponent<1, 0>(_var);}
void X(const vec_type_t<base_type_t<T>, 1>& _var) const { InsertComponent<1, 0>(var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = X, put = X)) TExtractType<1> x;
__declspec(property(get = X, put = X)) TExtractType<1> r;
TExtractType<2> XX() const { return ExtractComponent<2, 0, 0>(); } 
template <spv::StorageClass C1> void XX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 0, 0>(_var);}
void XX(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XX, put = XX)) TExtractType<2> xx;
__declspec(property(get = XX, put = XX)) TExtractType<2> rr;
TExtractType<3> XXX() const { return ExtractComponent<3, 0, 0, 0>(); } 
template <spv::StorageClass C1> void XXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 0>(_var);}
void XXX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXX, put = XXX)) TExtractType<3> xxx;
__declspec(property(get = XXX, put = XXX)) TExtractType<3> rrr;
TExtractType<4> XXXX() const { return ExtractComponent<3, 0, 0, 0, 0>(); } 
template <spv::StorageClass C1> void XXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 0, 0>(_var);}
void XXXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXXX, put = XXXX)) TExtractType<4> xxxx;
__declspec(property(get = XXXX, put = XXXX)) TExtractType<4> rrrr;
TExtractType<4> XXXY() const { return ExtractComponent<3, 0, 0, 0, 1>(); } 
template <spv::StorageClass C1> void XXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 0, 1>(_var);}
void XXXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXXY, put = XXXY)) TExtractType<4> xxxy;
__declspec(property(get = XXXY, put = XXXY)) TExtractType<4> rrrg;
TExtractType<4> XXXZ() const { return ExtractComponent<3, 0, 0, 0, 2>(); } 
template <spv::StorageClass C1> void XXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 0, 2>(_var);}
void XXXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXXZ, put = XXXZ)) TExtractType<4> xxxz;
__declspec(property(get = XXXZ, put = XXXZ)) TExtractType<4> rrrb;
TExtractType<4> XXXW() const { return ExtractComponent<3, 0, 0, 0, 3>(); } 
template <spv::StorageClass C1> void XXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 0, 3>(_var);}
void XXXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXXW, put = XXXW)) TExtractType<4> xxxw;
__declspec(property(get = XXXW, put = XXXW)) TExtractType<4> rrra;
TExtractType<3> XXY() const { return ExtractComponent<3, 0, 0, 1>(); } 
template <spv::StorageClass C1> void XXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 1>(_var);}
void XXY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXY, put = XXY)) TExtractType<3> xxy;
__declspec(property(get = XXY, put = XXY)) TExtractType<3> rrg;
TExtractType<4> XXYX() const { return ExtractComponent<3, 0, 0, 1, 0>(); } 
template <spv::StorageClass C1> void XXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 1, 0>(_var);}
void XXYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXYX, put = XXYX)) TExtractType<4> xxyx;
__declspec(property(get = XXYX, put = XXYX)) TExtractType<4> rrgr;
TExtractType<4> XXYY() const { return ExtractComponent<3, 0, 0, 1, 1>(); } 
template <spv::StorageClass C1> void XXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 1, 1>(_var);}
void XXYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXYY, put = XXYY)) TExtractType<4> xxyy;
__declspec(property(get = XXYY, put = XXYY)) TExtractType<4> rrgg;
TExtractType<4> XXYZ() const { return ExtractComponent<3, 0, 0, 1, 2>(); } 
template <spv::StorageClass C1> void XXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 1, 2>(_var);}
void XXYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXYZ, put = XXYZ)) TExtractType<4> xxyz;
__declspec(property(get = XXYZ, put = XXYZ)) TExtractType<4> rrgb;
TExtractType<4> XXYW() const { return ExtractComponent<3, 0, 0, 1, 3>(); } 
template <spv::StorageClass C1> void XXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 1, 3>(_var);}
void XXYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXYW, put = XXYW)) TExtractType<4> xxyw;
__declspec(property(get = XXYW, put = XXYW)) TExtractType<4> rrga;
TExtractType<3> XXZ() const { return ExtractComponent<3, 0, 0, 2>(); } 
template <spv::StorageClass C1> void XXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 2>(_var);}
void XXZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZ, put = XXZ)) TExtractType<3> xxz;
__declspec(property(get = XXZ, put = XXZ)) TExtractType<3> rrb;
TExtractType<4> XXZX() const { return ExtractComponent<3, 0, 0, 2, 0>(); } 
template <spv::StorageClass C1> void XXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 2, 0>(_var);}
void XXZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZX, put = XXZX)) TExtractType<4> xxzx;
__declspec(property(get = XXZX, put = XXZX)) TExtractType<4> rrbr;
TExtractType<4> XXZY() const { return ExtractComponent<3, 0, 0, 2, 1>(); } 
template <spv::StorageClass C1> void XXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 2, 1>(_var);}
void XXZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZY, put = XXZY)) TExtractType<4> xxzy;
__declspec(property(get = XXZY, put = XXZY)) TExtractType<4> rrbg;
TExtractType<4> XXZZ() const { return ExtractComponent<3, 0, 0, 2, 2>(); } 
template <spv::StorageClass C1> void XXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 2, 2>(_var);}
void XXZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZZ, put = XXZZ)) TExtractType<4> xxzz;
__declspec(property(get = XXZZ, put = XXZZ)) TExtractType<4> rrbb;
TExtractType<4> XXZW() const { return ExtractComponent<3, 0, 0, 2, 3>(); } 
template <spv::StorageClass C1> void XXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 2, 3>(_var);}
void XXZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXZW, put = XXZW)) TExtractType<4> xxzw;
__declspec(property(get = XXZW, put = XXZW)) TExtractType<4> rrba;
TExtractType<3> XXW() const { return ExtractComponent<3, 0, 0, 3>(); } 
template <spv::StorageClass C1> void XXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 3>(_var);}
void XXW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXW, put = XXW)) TExtractType<3> xxw;
__declspec(property(get = XXW, put = XXW)) TExtractType<3> rra;
TExtractType<4> XXWX() const { return ExtractComponent<3, 0, 0, 3, 0>(); } 
template <spv::StorageClass C1> void XXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 3, 0>(_var);}
void XXWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXWX, put = XXWX)) TExtractType<4> xxwx;
__declspec(property(get = XXWX, put = XXWX)) TExtractType<4> rrar;
TExtractType<4> XXWY() const { return ExtractComponent<3, 0, 0, 3, 1>(); } 
template <spv::StorageClass C1> void XXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 3, 1>(_var);}
void XXWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXWY, put = XXWY)) TExtractType<4> xxwy;
__declspec(property(get = XXWY, put = XXWY)) TExtractType<4> rrag;
TExtractType<4> XXWZ() const { return ExtractComponent<3, 0, 0, 3, 2>(); } 
template <spv::StorageClass C1> void XXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 3, 2>(_var);}
void XXWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXWZ, put = XXWZ)) TExtractType<4> xxwz;
__declspec(property(get = XXWZ, put = XXWZ)) TExtractType<4> rrab;
TExtractType<4> XXWW() const { return ExtractComponent<3, 0, 0, 3, 3>(); } 
template <spv::StorageClass C1> void XXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 0, 3, 3>(_var);}
void XXWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XXWW, put = XXWW)) TExtractType<4> xxww;
__declspec(property(get = XXWW, put = XXWW)) TExtractType<4> rraa;
TExtractType<2> XY() const { return ExtractComponent<2, 0, 1>(); } 
template <spv::StorageClass C1> void XY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 0, 1>(_var);}
void XY(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XY, put = XY)) TExtractType<2> xy;
__declspec(property(get = XY, put = XY)) TExtractType<2> rg;
TExtractType<3> XYX() const { return ExtractComponent<3, 0, 1, 0>(); } 
template <spv::StorageClass C1> void XYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 0>(_var);}
void XYX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYX, put = XYX)) TExtractType<3> xyx;
__declspec(property(get = XYX, put = XYX)) TExtractType<3> rgr;
TExtractType<4> XYXX() const { return ExtractComponent<3, 0, 1, 0, 0>(); } 
template <spv::StorageClass C1> void XYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 0, 0>(_var);}
void XYXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYXX, put = XYXX)) TExtractType<4> xyxx;
__declspec(property(get = XYXX, put = XYXX)) TExtractType<4> rgrr;
TExtractType<4> XYXY() const { return ExtractComponent<3, 0, 1, 0, 1>(); } 
template <spv::StorageClass C1> void XYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 0, 1>(_var);}
void XYXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYXY, put = XYXY)) TExtractType<4> xyxy;
__declspec(property(get = XYXY, put = XYXY)) TExtractType<4> rgrg;
TExtractType<4> XYXZ() const { return ExtractComponent<3, 0, 1, 0, 2>(); } 
template <spv::StorageClass C1> void XYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 0, 2>(_var);}
void XYXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYXZ, put = XYXZ)) TExtractType<4> xyxz;
__declspec(property(get = XYXZ, put = XYXZ)) TExtractType<4> rgrb;
TExtractType<4> XYXW() const { return ExtractComponent<3, 0, 1, 0, 3>(); } 
template <spv::StorageClass C1> void XYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 0, 3>(_var);}
void XYXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYXW, put = XYXW)) TExtractType<4> xyxw;
__declspec(property(get = XYXW, put = XYXW)) TExtractType<4> rgra;
TExtractType<3> XYY() const { return ExtractComponent<3, 0, 1, 1>(); } 
template <spv::StorageClass C1> void XYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 1>(_var);}
void XYY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYY, put = XYY)) TExtractType<3> xyy;
__declspec(property(get = XYY, put = XYY)) TExtractType<3> rgg;
TExtractType<4> XYYX() const { return ExtractComponent<3, 0, 1, 1, 0>(); } 
template <spv::StorageClass C1> void XYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 1, 0>(_var);}
void XYYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYYX, put = XYYX)) TExtractType<4> xyyx;
__declspec(property(get = XYYX, put = XYYX)) TExtractType<4> rggr;
TExtractType<4> XYYY() const { return ExtractComponent<3, 0, 1, 1, 1>(); } 
template <spv::StorageClass C1> void XYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 1, 1>(_var);}
void XYYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYYY, put = XYYY)) TExtractType<4> xyyy;
__declspec(property(get = XYYY, put = XYYY)) TExtractType<4> rggg;
TExtractType<4> XYYZ() const { return ExtractComponent<3, 0, 1, 1, 2>(); } 
template <spv::StorageClass C1> void XYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 1, 2>(_var);}
void XYYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYYZ, put = XYYZ)) TExtractType<4> xyyz;
__declspec(property(get = XYYZ, put = XYYZ)) TExtractType<4> rggb;
TExtractType<4> XYYW() const { return ExtractComponent<3, 0, 1, 1, 3>(); } 
template <spv::StorageClass C1> void XYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 1, 3>(_var);}
void XYYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYYW, put = XYYW)) TExtractType<4> xyyw;
__declspec(property(get = XYYW, put = XYYW)) TExtractType<4> rgga;
TExtractType<3> XYZ() const { return ExtractComponent<3, 0, 1, 2>(); } 
template <spv::StorageClass C1> void XYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 2>(_var);}
void XYZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZ, put = XYZ)) TExtractType<3> xyz;
__declspec(property(get = XYZ, put = XYZ)) TExtractType<3> rgb;
TExtractType<4> XYZX() const { return ExtractComponent<3, 0, 1, 2, 0>(); } 
template <spv::StorageClass C1> void XYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 2, 0>(_var);}
void XYZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZX, put = XYZX)) TExtractType<4> xyzx;
__declspec(property(get = XYZX, put = XYZX)) TExtractType<4> rgbr;
TExtractType<4> XYZY() const { return ExtractComponent<3, 0, 1, 2, 1>(); } 
template <spv::StorageClass C1> void XYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 2, 1>(_var);}
void XYZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZY, put = XYZY)) TExtractType<4> xyzy;
__declspec(property(get = XYZY, put = XYZY)) TExtractType<4> rgbg;
TExtractType<4> XYZZ() const { return ExtractComponent<3, 0, 1, 2, 2>(); } 
template <spv::StorageClass C1> void XYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 2, 2>(_var);}
void XYZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZZ, put = XYZZ)) TExtractType<4> xyzz;
__declspec(property(get = XYZZ, put = XYZZ)) TExtractType<4> rgbb;
TExtractType<4> XYZW() const { return ExtractComponent<3, 0, 1, 2, 3>(); } 
template <spv::StorageClass C1> void XYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 2, 3>(_var);}
void XYZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYZW, put = XYZW)) TExtractType<4> xyzw;
__declspec(property(get = XYZW, put = XYZW)) TExtractType<4> rgba;
TExtractType<3> XYW() const { return ExtractComponent<3, 0, 1, 3>(); } 
template <spv::StorageClass C1> void XYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 3>(_var);}
void XYW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYW, put = XYW)) TExtractType<3> xyw;
__declspec(property(get = XYW, put = XYW)) TExtractType<3> rga;
TExtractType<4> XYWX() const { return ExtractComponent<3, 0, 1, 3, 0>(); } 
template <spv::StorageClass C1> void XYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 3, 0>(_var);}
void XYWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYWX, put = XYWX)) TExtractType<4> xywx;
__declspec(property(get = XYWX, put = XYWX)) TExtractType<4> rgar;
TExtractType<4> XYWY() const { return ExtractComponent<3, 0, 1, 3, 1>(); } 
template <spv::StorageClass C1> void XYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 3, 1>(_var);}
void XYWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYWY, put = XYWY)) TExtractType<4> xywy;
__declspec(property(get = XYWY, put = XYWY)) TExtractType<4> rgag;
TExtractType<4> XYWZ() const { return ExtractComponent<3, 0, 1, 3, 2>(); } 
template <spv::StorageClass C1> void XYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 3, 2>(_var);}
void XYWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYWZ, put = XYWZ)) TExtractType<4> xywz;
__declspec(property(get = XYWZ, put = XYWZ)) TExtractType<4> rgab;
TExtractType<4> XYWW() const { return ExtractComponent<3, 0, 1, 3, 3>(); } 
template <spv::StorageClass C1> void XYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 1, 3, 3>(_var);}
void XYWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XYWW, put = XYWW)) TExtractType<4> xyww;
__declspec(property(get = XYWW, put = XYWW)) TExtractType<4> rgaa;
TExtractType<2> XZ() const { return ExtractComponent<2, 0, 2>(); } 
template <spv::StorageClass C1> void XZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 0, 2>(_var);}
void XZ(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZ, put = XZ)) TExtractType<2> xz;
__declspec(property(get = XZ, put = XZ)) TExtractType<2> rb;
TExtractType<3> XZX() const { return ExtractComponent<3, 0, 2, 0>(); } 
template <spv::StorageClass C1> void XZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 0>(_var);}
void XZX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZX, put = XZX)) TExtractType<3> xzx;
__declspec(property(get = XZX, put = XZX)) TExtractType<3> rbr;
TExtractType<4> XZXX() const { return ExtractComponent<3, 0, 2, 0, 0>(); } 
template <spv::StorageClass C1> void XZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 0, 0>(_var);}
void XZXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZXX, put = XZXX)) TExtractType<4> xzxx;
__declspec(property(get = XZXX, put = XZXX)) TExtractType<4> rbrr;
TExtractType<4> XZXY() const { return ExtractComponent<3, 0, 2, 0, 1>(); } 
template <spv::StorageClass C1> void XZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 0, 1>(_var);}
void XZXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZXY, put = XZXY)) TExtractType<4> xzxy;
__declspec(property(get = XZXY, put = XZXY)) TExtractType<4> rbrg;
TExtractType<4> XZXZ() const { return ExtractComponent<3, 0, 2, 0, 2>(); } 
template <spv::StorageClass C1> void XZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 0, 2>(_var);}
void XZXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZXZ, put = XZXZ)) TExtractType<4> xzxz;
__declspec(property(get = XZXZ, put = XZXZ)) TExtractType<4> rbrb;
TExtractType<4> XZXW() const { return ExtractComponent<3, 0, 2, 0, 3>(); } 
template <spv::StorageClass C1> void XZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 0, 3>(_var);}
void XZXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZXW, put = XZXW)) TExtractType<4> xzxw;
__declspec(property(get = XZXW, put = XZXW)) TExtractType<4> rbra;
TExtractType<3> XZY() const { return ExtractComponent<3, 0, 2, 1>(); } 
template <spv::StorageClass C1> void XZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 1>(_var);}
void XZY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZY, put = XZY)) TExtractType<3> xzy;
__declspec(property(get = XZY, put = XZY)) TExtractType<3> rbg;
TExtractType<4> XZYX() const { return ExtractComponent<3, 0, 2, 1, 0>(); } 
template <spv::StorageClass C1> void XZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 1, 0>(_var);}
void XZYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZYX, put = XZYX)) TExtractType<4> xzyx;
__declspec(property(get = XZYX, put = XZYX)) TExtractType<4> rbgr;
TExtractType<4> XZYY() const { return ExtractComponent<3, 0, 2, 1, 1>(); } 
template <spv::StorageClass C1> void XZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 1, 1>(_var);}
void XZYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZYY, put = XZYY)) TExtractType<4> xzyy;
__declspec(property(get = XZYY, put = XZYY)) TExtractType<4> rbgg;
TExtractType<4> XZYZ() const { return ExtractComponent<3, 0, 2, 1, 2>(); } 
template <spv::StorageClass C1> void XZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 1, 2>(_var);}
void XZYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZYZ, put = XZYZ)) TExtractType<4> xzyz;
__declspec(property(get = XZYZ, put = XZYZ)) TExtractType<4> rbgb;
TExtractType<4> XZYW() const { return ExtractComponent<3, 0, 2, 1, 3>(); } 
template <spv::StorageClass C1> void XZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 1, 3>(_var);}
void XZYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZYW, put = XZYW)) TExtractType<4> xzyw;
__declspec(property(get = XZYW, put = XZYW)) TExtractType<4> rbga;
TExtractType<3> XZZ() const { return ExtractComponent<3, 0, 2, 2>(); } 
template <spv::StorageClass C1> void XZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 2>(_var);}
void XZZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZ, put = XZZ)) TExtractType<3> xzz;
__declspec(property(get = XZZ, put = XZZ)) TExtractType<3> rbb;
TExtractType<4> XZZX() const { return ExtractComponent<3, 0, 2, 2, 0>(); } 
template <spv::StorageClass C1> void XZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 2, 0>(_var);}
void XZZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZX, put = XZZX)) TExtractType<4> xzzx;
__declspec(property(get = XZZX, put = XZZX)) TExtractType<4> rbbr;
TExtractType<4> XZZY() const { return ExtractComponent<3, 0, 2, 2, 1>(); } 
template <spv::StorageClass C1> void XZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 2, 1>(_var);}
void XZZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZY, put = XZZY)) TExtractType<4> xzzy;
__declspec(property(get = XZZY, put = XZZY)) TExtractType<4> rbbg;
TExtractType<4> XZZZ() const { return ExtractComponent<3, 0, 2, 2, 2>(); } 
template <spv::StorageClass C1> void XZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 2, 2>(_var);}
void XZZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZZ, put = XZZZ)) TExtractType<4> xzzz;
__declspec(property(get = XZZZ, put = XZZZ)) TExtractType<4> rbbb;
TExtractType<4> XZZW() const { return ExtractComponent<3, 0, 2, 2, 3>(); } 
template <spv::StorageClass C1> void XZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 2, 3>(_var);}
void XZZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZZW, put = XZZW)) TExtractType<4> xzzw;
__declspec(property(get = XZZW, put = XZZW)) TExtractType<4> rbba;
TExtractType<3> XZW() const { return ExtractComponent<3, 0, 2, 3>(); } 
template <spv::StorageClass C1> void XZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 3>(_var);}
void XZW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZW, put = XZW)) TExtractType<3> xzw;
__declspec(property(get = XZW, put = XZW)) TExtractType<3> rba;
TExtractType<4> XZWX() const { return ExtractComponent<3, 0, 2, 3, 0>(); } 
template <spv::StorageClass C1> void XZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 3, 0>(_var);}
void XZWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZWX, put = XZWX)) TExtractType<4> xzwx;
__declspec(property(get = XZWX, put = XZWX)) TExtractType<4> rbar;
TExtractType<4> XZWY() const { return ExtractComponent<3, 0, 2, 3, 1>(); } 
template <spv::StorageClass C1> void XZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 3, 1>(_var);}
void XZWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZWY, put = XZWY)) TExtractType<4> xzwy;
__declspec(property(get = XZWY, put = XZWY)) TExtractType<4> rbag;
TExtractType<4> XZWZ() const { return ExtractComponent<3, 0, 2, 3, 2>(); } 
template <spv::StorageClass C1> void XZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 3, 2>(_var);}
void XZWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZWZ, put = XZWZ)) TExtractType<4> xzwz;
__declspec(property(get = XZWZ, put = XZWZ)) TExtractType<4> rbab;
TExtractType<4> XZWW() const { return ExtractComponent<3, 0, 2, 3, 3>(); } 
template <spv::StorageClass C1> void XZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 2, 3, 3>(_var);}
void XZWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XZWW, put = XZWW)) TExtractType<4> xzww;
__declspec(property(get = XZWW, put = XZWW)) TExtractType<4> rbaa;
TExtractType<2> XW() const { return ExtractComponent<2, 0, 3>(); } 
template <spv::StorageClass C1> void XW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 0, 3>(_var);}
void XW(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XW, put = XW)) TExtractType<2> xw;
__declspec(property(get = XW, put = XW)) TExtractType<2> ra;
TExtractType<3> XWX() const { return ExtractComponent<3, 0, 3, 0>(); } 
template <spv::StorageClass C1> void XWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 0>(_var);}
void XWX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWX, put = XWX)) TExtractType<3> xwx;
__declspec(property(get = XWX, put = XWX)) TExtractType<3> rar;
TExtractType<4> XWXX() const { return ExtractComponent<3, 0, 3, 0, 0>(); } 
template <spv::StorageClass C1> void XWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 0, 0>(_var);}
void XWXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWXX, put = XWXX)) TExtractType<4> xwxx;
__declspec(property(get = XWXX, put = XWXX)) TExtractType<4> rarr;
TExtractType<4> XWXY() const { return ExtractComponent<3, 0, 3, 0, 1>(); } 
template <spv::StorageClass C1> void XWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 0, 1>(_var);}
void XWXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWXY, put = XWXY)) TExtractType<4> xwxy;
__declspec(property(get = XWXY, put = XWXY)) TExtractType<4> rarg;
TExtractType<4> XWXZ() const { return ExtractComponent<3, 0, 3, 0, 2>(); } 
template <spv::StorageClass C1> void XWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 0, 2>(_var);}
void XWXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWXZ, put = XWXZ)) TExtractType<4> xwxz;
__declspec(property(get = XWXZ, put = XWXZ)) TExtractType<4> rarb;
TExtractType<4> XWXW() const { return ExtractComponent<3, 0, 3, 0, 3>(); } 
template <spv::StorageClass C1> void XWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 0, 3>(_var);}
void XWXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWXW, put = XWXW)) TExtractType<4> xwxw;
__declspec(property(get = XWXW, put = XWXW)) TExtractType<4> rara;
TExtractType<3> XWY() const { return ExtractComponent<3, 0, 3, 1>(); } 
template <spv::StorageClass C1> void XWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 1>(_var);}
void XWY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWY, put = XWY)) TExtractType<3> xwy;
__declspec(property(get = XWY, put = XWY)) TExtractType<3> rag;
TExtractType<4> XWYX() const { return ExtractComponent<3, 0, 3, 1, 0>(); } 
template <spv::StorageClass C1> void XWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 1, 0>(_var);}
void XWYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWYX, put = XWYX)) TExtractType<4> xwyx;
__declspec(property(get = XWYX, put = XWYX)) TExtractType<4> ragr;
TExtractType<4> XWYY() const { return ExtractComponent<3, 0, 3, 1, 1>(); } 
template <spv::StorageClass C1> void XWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 1, 1>(_var);}
void XWYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWYY, put = XWYY)) TExtractType<4> xwyy;
__declspec(property(get = XWYY, put = XWYY)) TExtractType<4> ragg;
TExtractType<4> XWYZ() const { return ExtractComponent<3, 0, 3, 1, 2>(); } 
template <spv::StorageClass C1> void XWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 1, 2>(_var);}
void XWYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWYZ, put = XWYZ)) TExtractType<4> xwyz;
__declspec(property(get = XWYZ, put = XWYZ)) TExtractType<4> ragb;
TExtractType<4> XWYW() const { return ExtractComponent<3, 0, 3, 1, 3>(); } 
template <spv::StorageClass C1> void XWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 1, 3>(_var);}
void XWYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWYW, put = XWYW)) TExtractType<4> xwyw;
__declspec(property(get = XWYW, put = XWYW)) TExtractType<4> raga;
TExtractType<3> XWZ() const { return ExtractComponent<3, 0, 3, 2>(); } 
template <spv::StorageClass C1> void XWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 2>(_var);}
void XWZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZ, put = XWZ)) TExtractType<3> xwz;
__declspec(property(get = XWZ, put = XWZ)) TExtractType<3> rab;
TExtractType<4> XWZX() const { return ExtractComponent<3, 0, 3, 2, 0>(); } 
template <spv::StorageClass C1> void XWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 2, 0>(_var);}
void XWZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZX, put = XWZX)) TExtractType<4> xwzx;
__declspec(property(get = XWZX, put = XWZX)) TExtractType<4> rabr;
TExtractType<4> XWZY() const { return ExtractComponent<3, 0, 3, 2, 1>(); } 
template <spv::StorageClass C1> void XWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 2, 1>(_var);}
void XWZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZY, put = XWZY)) TExtractType<4> xwzy;
__declspec(property(get = XWZY, put = XWZY)) TExtractType<4> rabg;
TExtractType<4> XWZZ() const { return ExtractComponent<3, 0, 3, 2, 2>(); } 
template <spv::StorageClass C1> void XWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 2, 2>(_var);}
void XWZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZZ, put = XWZZ)) TExtractType<4> xwzz;
__declspec(property(get = XWZZ, put = XWZZ)) TExtractType<4> rabb;
TExtractType<4> XWZW() const { return ExtractComponent<3, 0, 3, 2, 3>(); } 
template <spv::StorageClass C1> void XWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 2, 3>(_var);}
void XWZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWZW, put = XWZW)) TExtractType<4> xwzw;
__declspec(property(get = XWZW, put = XWZW)) TExtractType<4> raba;
TExtractType<3> XWW() const { return ExtractComponent<3, 0, 3, 3>(); } 
template <spv::StorageClass C1> void XWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 3>(_var);}
void XWW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWW, put = XWW)) TExtractType<3> xww;
__declspec(property(get = XWW, put = XWW)) TExtractType<3> raa;
TExtractType<4> XWWX() const { return ExtractComponent<3, 0, 3, 3, 0>(); } 
template <spv::StorageClass C1> void XWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 3, 0>(_var);}
void XWWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWWX, put = XWWX)) TExtractType<4> xwwx;
__declspec(property(get = XWWX, put = XWWX)) TExtractType<4> raar;
TExtractType<4> XWWY() const { return ExtractComponent<3, 0, 3, 3, 1>(); } 
template <spv::StorageClass C1> void XWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 3, 1>(_var);}
void XWWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWWY, put = XWWY)) TExtractType<4> xwwy;
__declspec(property(get = XWWY, put = XWWY)) TExtractType<4> raag;
TExtractType<4> XWWZ() const { return ExtractComponent<3, 0, 3, 3, 2>(); } 
template <spv::StorageClass C1> void XWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 3, 2>(_var);}
void XWWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWWZ, put = XWWZ)) TExtractType<4> xwwz;
__declspec(property(get = XWWZ, put = XWWZ)) TExtractType<4> raab;
TExtractType<4> XWWW() const { return ExtractComponent<3, 0, 3, 3, 3>(); } 
template <spv::StorageClass C1> void XWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 0, 3, 3, 3>(_var);}
void XWWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 0, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = XWWW, put = XWWW)) TExtractType<4> xwww;
__declspec(property(get = XWWW, put = XWWW)) TExtractType<4> raaa;
TExtractType<1> Y() const { return ExtractComponent<1, 1>(); } 
template <spv::StorageClass C1> void Y(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) const { InsertComponent<1, 1>(_var);}
void Y(const vec_type_t<base_type_t<T>, 1>& _var) const { InsertComponent<1, 1>(var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = Y, put = Y)) TExtractType<1> y;
__declspec(property(get = Y, put = Y)) TExtractType<1> g;
TExtractType<2> YX() const { return ExtractComponent<2, 1, 0>(); } 
template <spv::StorageClass C1> void YX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 1, 0>(_var);}
void YX(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YX, put = YX)) TExtractType<2> yx;
__declspec(property(get = YX, put = YX)) TExtractType<2> gr;
TExtractType<3> YXX() const { return ExtractComponent<3, 1, 0, 0>(); } 
template <spv::StorageClass C1> void YXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 0>(_var);}
void YXX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXX, put = YXX)) TExtractType<3> yxx;
__declspec(property(get = YXX, put = YXX)) TExtractType<3> grr;
TExtractType<4> YXXX() const { return ExtractComponent<3, 1, 0, 0, 0>(); } 
template <spv::StorageClass C1> void YXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 0, 0>(_var);}
void YXXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXXX, put = YXXX)) TExtractType<4> yxxx;
__declspec(property(get = YXXX, put = YXXX)) TExtractType<4> grrr;
TExtractType<4> YXXY() const { return ExtractComponent<3, 1, 0, 0, 1>(); } 
template <spv::StorageClass C1> void YXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 0, 1>(_var);}
void YXXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXXY, put = YXXY)) TExtractType<4> yxxy;
__declspec(property(get = YXXY, put = YXXY)) TExtractType<4> grrg;
TExtractType<4> YXXZ() const { return ExtractComponent<3, 1, 0, 0, 2>(); } 
template <spv::StorageClass C1> void YXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 0, 2>(_var);}
void YXXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXXZ, put = YXXZ)) TExtractType<4> yxxz;
__declspec(property(get = YXXZ, put = YXXZ)) TExtractType<4> grrb;
TExtractType<4> YXXW() const { return ExtractComponent<3, 1, 0, 0, 3>(); } 
template <spv::StorageClass C1> void YXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 0, 3>(_var);}
void YXXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXXW, put = YXXW)) TExtractType<4> yxxw;
__declspec(property(get = YXXW, put = YXXW)) TExtractType<4> grra;
TExtractType<3> YXY() const { return ExtractComponent<3, 1, 0, 1>(); } 
template <spv::StorageClass C1> void YXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 1>(_var);}
void YXY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXY, put = YXY)) TExtractType<3> yxy;
__declspec(property(get = YXY, put = YXY)) TExtractType<3> grg;
TExtractType<4> YXYX() const { return ExtractComponent<3, 1, 0, 1, 0>(); } 
template <spv::StorageClass C1> void YXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 1, 0>(_var);}
void YXYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXYX, put = YXYX)) TExtractType<4> yxyx;
__declspec(property(get = YXYX, put = YXYX)) TExtractType<4> grgr;
TExtractType<4> YXYY() const { return ExtractComponent<3, 1, 0, 1, 1>(); } 
template <spv::StorageClass C1> void YXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 1, 1>(_var);}
void YXYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXYY, put = YXYY)) TExtractType<4> yxyy;
__declspec(property(get = YXYY, put = YXYY)) TExtractType<4> grgg;
TExtractType<4> YXYZ() const { return ExtractComponent<3, 1, 0, 1, 2>(); } 
template <spv::StorageClass C1> void YXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 1, 2>(_var);}
void YXYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXYZ, put = YXYZ)) TExtractType<4> yxyz;
__declspec(property(get = YXYZ, put = YXYZ)) TExtractType<4> grgb;
TExtractType<4> YXYW() const { return ExtractComponent<3, 1, 0, 1, 3>(); } 
template <spv::StorageClass C1> void YXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 1, 3>(_var);}
void YXYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXYW, put = YXYW)) TExtractType<4> yxyw;
__declspec(property(get = YXYW, put = YXYW)) TExtractType<4> grga;
TExtractType<3> YXZ() const { return ExtractComponent<3, 1, 0, 2>(); } 
template <spv::StorageClass C1> void YXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 2>(_var);}
void YXZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZ, put = YXZ)) TExtractType<3> yxz;
__declspec(property(get = YXZ, put = YXZ)) TExtractType<3> grb;
TExtractType<4> YXZX() const { return ExtractComponent<3, 1, 0, 2, 0>(); } 
template <spv::StorageClass C1> void YXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 2, 0>(_var);}
void YXZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZX, put = YXZX)) TExtractType<4> yxzx;
__declspec(property(get = YXZX, put = YXZX)) TExtractType<4> grbr;
TExtractType<4> YXZY() const { return ExtractComponent<3, 1, 0, 2, 1>(); } 
template <spv::StorageClass C1> void YXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 2, 1>(_var);}
void YXZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZY, put = YXZY)) TExtractType<4> yxzy;
__declspec(property(get = YXZY, put = YXZY)) TExtractType<4> grbg;
TExtractType<4> YXZZ() const { return ExtractComponent<3, 1, 0, 2, 2>(); } 
template <spv::StorageClass C1> void YXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 2, 2>(_var);}
void YXZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZZ, put = YXZZ)) TExtractType<4> yxzz;
__declspec(property(get = YXZZ, put = YXZZ)) TExtractType<4> grbb;
TExtractType<4> YXZW() const { return ExtractComponent<3, 1, 0, 2, 3>(); } 
template <spv::StorageClass C1> void YXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 2, 3>(_var);}
void YXZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXZW, put = YXZW)) TExtractType<4> yxzw;
__declspec(property(get = YXZW, put = YXZW)) TExtractType<4> grba;
TExtractType<3> YXW() const { return ExtractComponent<3, 1, 0, 3>(); } 
template <spv::StorageClass C1> void YXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 3>(_var);}
void YXW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXW, put = YXW)) TExtractType<3> yxw;
__declspec(property(get = YXW, put = YXW)) TExtractType<3> gra;
TExtractType<4> YXWX() const { return ExtractComponent<3, 1, 0, 3, 0>(); } 
template <spv::StorageClass C1> void YXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 3, 0>(_var);}
void YXWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXWX, put = YXWX)) TExtractType<4> yxwx;
__declspec(property(get = YXWX, put = YXWX)) TExtractType<4> grar;
TExtractType<4> YXWY() const { return ExtractComponent<3, 1, 0, 3, 1>(); } 
template <spv::StorageClass C1> void YXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 3, 1>(_var);}
void YXWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXWY, put = YXWY)) TExtractType<4> yxwy;
__declspec(property(get = YXWY, put = YXWY)) TExtractType<4> grag;
TExtractType<4> YXWZ() const { return ExtractComponent<3, 1, 0, 3, 2>(); } 
template <spv::StorageClass C1> void YXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 3, 2>(_var);}
void YXWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXWZ, put = YXWZ)) TExtractType<4> yxwz;
__declspec(property(get = YXWZ, put = YXWZ)) TExtractType<4> grab;
TExtractType<4> YXWW() const { return ExtractComponent<3, 1, 0, 3, 3>(); } 
template <spv::StorageClass C1> void YXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 0, 3, 3>(_var);}
void YXWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YXWW, put = YXWW)) TExtractType<4> yxww;
__declspec(property(get = YXWW, put = YXWW)) TExtractType<4> graa;
TExtractType<2> YY() const { return ExtractComponent<2, 1, 1>(); } 
template <spv::StorageClass C1> void YY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 1, 1>(_var);}
void YY(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YY, put = YY)) TExtractType<2> yy;
__declspec(property(get = YY, put = YY)) TExtractType<2> gg;
TExtractType<3> YYX() const { return ExtractComponent<3, 1, 1, 0>(); } 
template <spv::StorageClass C1> void YYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 0>(_var);}
void YYX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYX, put = YYX)) TExtractType<3> yyx;
__declspec(property(get = YYX, put = YYX)) TExtractType<3> ggr;
TExtractType<4> YYXX() const { return ExtractComponent<3, 1, 1, 0, 0>(); } 
template <spv::StorageClass C1> void YYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 0, 0>(_var);}
void YYXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYXX, put = YYXX)) TExtractType<4> yyxx;
__declspec(property(get = YYXX, put = YYXX)) TExtractType<4> ggrr;
TExtractType<4> YYXY() const { return ExtractComponent<3, 1, 1, 0, 1>(); } 
template <spv::StorageClass C1> void YYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 0, 1>(_var);}
void YYXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYXY, put = YYXY)) TExtractType<4> yyxy;
__declspec(property(get = YYXY, put = YYXY)) TExtractType<4> ggrg;
TExtractType<4> YYXZ() const { return ExtractComponent<3, 1, 1, 0, 2>(); } 
template <spv::StorageClass C1> void YYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 0, 2>(_var);}
void YYXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYXZ, put = YYXZ)) TExtractType<4> yyxz;
__declspec(property(get = YYXZ, put = YYXZ)) TExtractType<4> ggrb;
TExtractType<4> YYXW() const { return ExtractComponent<3, 1, 1, 0, 3>(); } 
template <spv::StorageClass C1> void YYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 0, 3>(_var);}
void YYXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYXW, put = YYXW)) TExtractType<4> yyxw;
__declspec(property(get = YYXW, put = YYXW)) TExtractType<4> ggra;
TExtractType<3> YYY() const { return ExtractComponent<3, 1, 1, 1>(); } 
template <spv::StorageClass C1> void YYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 1>(_var);}
void YYY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYY, put = YYY)) TExtractType<3> yyy;
__declspec(property(get = YYY, put = YYY)) TExtractType<3> ggg;
TExtractType<4> YYYX() const { return ExtractComponent<3, 1, 1, 1, 0>(); } 
template <spv::StorageClass C1> void YYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 1, 0>(_var);}
void YYYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYYX, put = YYYX)) TExtractType<4> yyyx;
__declspec(property(get = YYYX, put = YYYX)) TExtractType<4> gggr;
TExtractType<4> YYYY() const { return ExtractComponent<3, 1, 1, 1, 1>(); } 
template <spv::StorageClass C1> void YYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 1, 1>(_var);}
void YYYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYYY, put = YYYY)) TExtractType<4> yyyy;
__declspec(property(get = YYYY, put = YYYY)) TExtractType<4> gggg;
TExtractType<4> YYYZ() const { return ExtractComponent<3, 1, 1, 1, 2>(); } 
template <spv::StorageClass C1> void YYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 1, 2>(_var);}
void YYYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYYZ, put = YYYZ)) TExtractType<4> yyyz;
__declspec(property(get = YYYZ, put = YYYZ)) TExtractType<4> gggb;
TExtractType<4> YYYW() const { return ExtractComponent<3, 1, 1, 1, 3>(); } 
template <spv::StorageClass C1> void YYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 1, 3>(_var);}
void YYYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYYW, put = YYYW)) TExtractType<4> yyyw;
__declspec(property(get = YYYW, put = YYYW)) TExtractType<4> ggga;
TExtractType<3> YYZ() const { return ExtractComponent<3, 1, 1, 2>(); } 
template <spv::StorageClass C1> void YYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 2>(_var);}
void YYZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZ, put = YYZ)) TExtractType<3> yyz;
__declspec(property(get = YYZ, put = YYZ)) TExtractType<3> ggb;
TExtractType<4> YYZX() const { return ExtractComponent<3, 1, 1, 2, 0>(); } 
template <spv::StorageClass C1> void YYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 2, 0>(_var);}
void YYZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZX, put = YYZX)) TExtractType<4> yyzx;
__declspec(property(get = YYZX, put = YYZX)) TExtractType<4> ggbr;
TExtractType<4> YYZY() const { return ExtractComponent<3, 1, 1, 2, 1>(); } 
template <spv::StorageClass C1> void YYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 2, 1>(_var);}
void YYZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZY, put = YYZY)) TExtractType<4> yyzy;
__declspec(property(get = YYZY, put = YYZY)) TExtractType<4> ggbg;
TExtractType<4> YYZZ() const { return ExtractComponent<3, 1, 1, 2, 2>(); } 
template <spv::StorageClass C1> void YYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 2, 2>(_var);}
void YYZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZZ, put = YYZZ)) TExtractType<4> yyzz;
__declspec(property(get = YYZZ, put = YYZZ)) TExtractType<4> ggbb;
TExtractType<4> YYZW() const { return ExtractComponent<3, 1, 1, 2, 3>(); } 
template <spv::StorageClass C1> void YYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 2, 3>(_var);}
void YYZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYZW, put = YYZW)) TExtractType<4> yyzw;
__declspec(property(get = YYZW, put = YYZW)) TExtractType<4> ggba;
TExtractType<3> YYW() const { return ExtractComponent<3, 1, 1, 3>(); } 
template <spv::StorageClass C1> void YYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 3>(_var);}
void YYW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYW, put = YYW)) TExtractType<3> yyw;
__declspec(property(get = YYW, put = YYW)) TExtractType<3> gga;
TExtractType<4> YYWX() const { return ExtractComponent<3, 1, 1, 3, 0>(); } 
template <spv::StorageClass C1> void YYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 3, 0>(_var);}
void YYWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYWX, put = YYWX)) TExtractType<4> yywx;
__declspec(property(get = YYWX, put = YYWX)) TExtractType<4> ggar;
TExtractType<4> YYWY() const { return ExtractComponent<3, 1, 1, 3, 1>(); } 
template <spv::StorageClass C1> void YYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 3, 1>(_var);}
void YYWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYWY, put = YYWY)) TExtractType<4> yywy;
__declspec(property(get = YYWY, put = YYWY)) TExtractType<4> ggag;
TExtractType<4> YYWZ() const { return ExtractComponent<3, 1, 1, 3, 2>(); } 
template <spv::StorageClass C1> void YYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 3, 2>(_var);}
void YYWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYWZ, put = YYWZ)) TExtractType<4> yywz;
__declspec(property(get = YYWZ, put = YYWZ)) TExtractType<4> ggab;
TExtractType<4> YYWW() const { return ExtractComponent<3, 1, 1, 3, 3>(); } 
template <spv::StorageClass C1> void YYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 1, 3, 3>(_var);}
void YYWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YYWW, put = YYWW)) TExtractType<4> yyww;
__declspec(property(get = YYWW, put = YYWW)) TExtractType<4> ggaa;
TExtractType<2> YZ() const { return ExtractComponent<2, 1, 2>(); } 
template <spv::StorageClass C1> void YZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 1, 2>(_var);}
void YZ(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZ, put = YZ)) TExtractType<2> yz;
__declspec(property(get = YZ, put = YZ)) TExtractType<2> gb;
TExtractType<3> YZX() const { return ExtractComponent<3, 1, 2, 0>(); } 
template <spv::StorageClass C1> void YZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 0>(_var);}
void YZX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZX, put = YZX)) TExtractType<3> yzx;
__declspec(property(get = YZX, put = YZX)) TExtractType<3> gbr;
TExtractType<4> YZXX() const { return ExtractComponent<3, 1, 2, 0, 0>(); } 
template <spv::StorageClass C1> void YZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 0, 0>(_var);}
void YZXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZXX, put = YZXX)) TExtractType<4> yzxx;
__declspec(property(get = YZXX, put = YZXX)) TExtractType<4> gbrr;
TExtractType<4> YZXY() const { return ExtractComponent<3, 1, 2, 0, 1>(); } 
template <spv::StorageClass C1> void YZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 0, 1>(_var);}
void YZXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZXY, put = YZXY)) TExtractType<4> yzxy;
__declspec(property(get = YZXY, put = YZXY)) TExtractType<4> gbrg;
TExtractType<4> YZXZ() const { return ExtractComponent<3, 1, 2, 0, 2>(); } 
template <spv::StorageClass C1> void YZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 0, 2>(_var);}
void YZXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZXZ, put = YZXZ)) TExtractType<4> yzxz;
__declspec(property(get = YZXZ, put = YZXZ)) TExtractType<4> gbrb;
TExtractType<4> YZXW() const { return ExtractComponent<3, 1, 2, 0, 3>(); } 
template <spv::StorageClass C1> void YZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 0, 3>(_var);}
void YZXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZXW, put = YZXW)) TExtractType<4> yzxw;
__declspec(property(get = YZXW, put = YZXW)) TExtractType<4> gbra;
TExtractType<3> YZY() const { return ExtractComponent<3, 1, 2, 1>(); } 
template <spv::StorageClass C1> void YZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 1>(_var);}
void YZY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZY, put = YZY)) TExtractType<3> yzy;
__declspec(property(get = YZY, put = YZY)) TExtractType<3> gbg;
TExtractType<4> YZYX() const { return ExtractComponent<3, 1, 2, 1, 0>(); } 
template <spv::StorageClass C1> void YZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 1, 0>(_var);}
void YZYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZYX, put = YZYX)) TExtractType<4> yzyx;
__declspec(property(get = YZYX, put = YZYX)) TExtractType<4> gbgr;
TExtractType<4> YZYY() const { return ExtractComponent<3, 1, 2, 1, 1>(); } 
template <spv::StorageClass C1> void YZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 1, 1>(_var);}
void YZYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZYY, put = YZYY)) TExtractType<4> yzyy;
__declspec(property(get = YZYY, put = YZYY)) TExtractType<4> gbgg;
TExtractType<4> YZYZ() const { return ExtractComponent<3, 1, 2, 1, 2>(); } 
template <spv::StorageClass C1> void YZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 1, 2>(_var);}
void YZYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZYZ, put = YZYZ)) TExtractType<4> yzyz;
__declspec(property(get = YZYZ, put = YZYZ)) TExtractType<4> gbgb;
TExtractType<4> YZYW() const { return ExtractComponent<3, 1, 2, 1, 3>(); } 
template <spv::StorageClass C1> void YZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 1, 3>(_var);}
void YZYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZYW, put = YZYW)) TExtractType<4> yzyw;
__declspec(property(get = YZYW, put = YZYW)) TExtractType<4> gbga;
TExtractType<3> YZZ() const { return ExtractComponent<3, 1, 2, 2>(); } 
template <spv::StorageClass C1> void YZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 2>(_var);}
void YZZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZ, put = YZZ)) TExtractType<3> yzz;
__declspec(property(get = YZZ, put = YZZ)) TExtractType<3> gbb;
TExtractType<4> YZZX() const { return ExtractComponent<3, 1, 2, 2, 0>(); } 
template <spv::StorageClass C1> void YZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 2, 0>(_var);}
void YZZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZX, put = YZZX)) TExtractType<4> yzzx;
__declspec(property(get = YZZX, put = YZZX)) TExtractType<4> gbbr;
TExtractType<4> YZZY() const { return ExtractComponent<3, 1, 2, 2, 1>(); } 
template <spv::StorageClass C1> void YZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 2, 1>(_var);}
void YZZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZY, put = YZZY)) TExtractType<4> yzzy;
__declspec(property(get = YZZY, put = YZZY)) TExtractType<4> gbbg;
TExtractType<4> YZZZ() const { return ExtractComponent<3, 1, 2, 2, 2>(); } 
template <spv::StorageClass C1> void YZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 2, 2>(_var);}
void YZZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZZ, put = YZZZ)) TExtractType<4> yzzz;
__declspec(property(get = YZZZ, put = YZZZ)) TExtractType<4> gbbb;
TExtractType<4> YZZW() const { return ExtractComponent<3, 1, 2, 2, 3>(); } 
template <spv::StorageClass C1> void YZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 2, 3>(_var);}
void YZZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZZW, put = YZZW)) TExtractType<4> yzzw;
__declspec(property(get = YZZW, put = YZZW)) TExtractType<4> gbba;
TExtractType<3> YZW() const { return ExtractComponent<3, 1, 2, 3>(); } 
template <spv::StorageClass C1> void YZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 3>(_var);}
void YZW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZW, put = YZW)) TExtractType<3> yzw;
__declspec(property(get = YZW, put = YZW)) TExtractType<3> gba;
TExtractType<4> YZWX() const { return ExtractComponent<3, 1, 2, 3, 0>(); } 
template <spv::StorageClass C1> void YZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 3, 0>(_var);}
void YZWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZWX, put = YZWX)) TExtractType<4> yzwx;
__declspec(property(get = YZWX, put = YZWX)) TExtractType<4> gbar;
TExtractType<4> YZWY() const { return ExtractComponent<3, 1, 2, 3, 1>(); } 
template <spv::StorageClass C1> void YZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 3, 1>(_var);}
void YZWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZWY, put = YZWY)) TExtractType<4> yzwy;
__declspec(property(get = YZWY, put = YZWY)) TExtractType<4> gbag;
TExtractType<4> YZWZ() const { return ExtractComponent<3, 1, 2, 3, 2>(); } 
template <spv::StorageClass C1> void YZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 3, 2>(_var);}
void YZWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZWZ, put = YZWZ)) TExtractType<4> yzwz;
__declspec(property(get = YZWZ, put = YZWZ)) TExtractType<4> gbab;
TExtractType<4> YZWW() const { return ExtractComponent<3, 1, 2, 3, 3>(); } 
template <spv::StorageClass C1> void YZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 2, 3, 3>(_var);}
void YZWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YZWW, put = YZWW)) TExtractType<4> yzww;
__declspec(property(get = YZWW, put = YZWW)) TExtractType<4> gbaa;
TExtractType<2> YW() const { return ExtractComponent<2, 1, 3>(); } 
template <spv::StorageClass C1> void YW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 1, 3>(_var);}
void YW(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YW, put = YW)) TExtractType<2> yw;
__declspec(property(get = YW, put = YW)) TExtractType<2> ga;
TExtractType<3> YWX() const { return ExtractComponent<3, 1, 3, 0>(); } 
template <spv::StorageClass C1> void YWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 0>(_var);}
void YWX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWX, put = YWX)) TExtractType<3> ywx;
__declspec(property(get = YWX, put = YWX)) TExtractType<3> gar;
TExtractType<4> YWXX() const { return ExtractComponent<3, 1, 3, 0, 0>(); } 
template <spv::StorageClass C1> void YWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 0, 0>(_var);}
void YWXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWXX, put = YWXX)) TExtractType<4> ywxx;
__declspec(property(get = YWXX, put = YWXX)) TExtractType<4> garr;
TExtractType<4> YWXY() const { return ExtractComponent<3, 1, 3, 0, 1>(); } 
template <spv::StorageClass C1> void YWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 0, 1>(_var);}
void YWXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWXY, put = YWXY)) TExtractType<4> ywxy;
__declspec(property(get = YWXY, put = YWXY)) TExtractType<4> garg;
TExtractType<4> YWXZ() const { return ExtractComponent<3, 1, 3, 0, 2>(); } 
template <spv::StorageClass C1> void YWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 0, 2>(_var);}
void YWXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWXZ, put = YWXZ)) TExtractType<4> ywxz;
__declspec(property(get = YWXZ, put = YWXZ)) TExtractType<4> garb;
TExtractType<4> YWXW() const { return ExtractComponent<3, 1, 3, 0, 3>(); } 
template <spv::StorageClass C1> void YWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 0, 3>(_var);}
void YWXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWXW, put = YWXW)) TExtractType<4> ywxw;
__declspec(property(get = YWXW, put = YWXW)) TExtractType<4> gara;
TExtractType<3> YWY() const { return ExtractComponent<3, 1, 3, 1>(); } 
template <spv::StorageClass C1> void YWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 1>(_var);}
void YWY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWY, put = YWY)) TExtractType<3> ywy;
__declspec(property(get = YWY, put = YWY)) TExtractType<3> gag;
TExtractType<4> YWYX() const { return ExtractComponent<3, 1, 3, 1, 0>(); } 
template <spv::StorageClass C1> void YWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 1, 0>(_var);}
void YWYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWYX, put = YWYX)) TExtractType<4> ywyx;
__declspec(property(get = YWYX, put = YWYX)) TExtractType<4> gagr;
TExtractType<4> YWYY() const { return ExtractComponent<3, 1, 3, 1, 1>(); } 
template <spv::StorageClass C1> void YWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 1, 1>(_var);}
void YWYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWYY, put = YWYY)) TExtractType<4> ywyy;
__declspec(property(get = YWYY, put = YWYY)) TExtractType<4> gagg;
TExtractType<4> YWYZ() const { return ExtractComponent<3, 1, 3, 1, 2>(); } 
template <spv::StorageClass C1> void YWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 1, 2>(_var);}
void YWYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWYZ, put = YWYZ)) TExtractType<4> ywyz;
__declspec(property(get = YWYZ, put = YWYZ)) TExtractType<4> gagb;
TExtractType<4> YWYW() const { return ExtractComponent<3, 1, 3, 1, 3>(); } 
template <spv::StorageClass C1> void YWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 1, 3>(_var);}
void YWYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWYW, put = YWYW)) TExtractType<4> ywyw;
__declspec(property(get = YWYW, put = YWYW)) TExtractType<4> gaga;
TExtractType<3> YWZ() const { return ExtractComponent<3, 1, 3, 2>(); } 
template <spv::StorageClass C1> void YWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 2>(_var);}
void YWZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZ, put = YWZ)) TExtractType<3> ywz;
__declspec(property(get = YWZ, put = YWZ)) TExtractType<3> gab;
TExtractType<4> YWZX() const { return ExtractComponent<3, 1, 3, 2, 0>(); } 
template <spv::StorageClass C1> void YWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 2, 0>(_var);}
void YWZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZX, put = YWZX)) TExtractType<4> ywzx;
__declspec(property(get = YWZX, put = YWZX)) TExtractType<4> gabr;
TExtractType<4> YWZY() const { return ExtractComponent<3, 1, 3, 2, 1>(); } 
template <spv::StorageClass C1> void YWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 2, 1>(_var);}
void YWZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZY, put = YWZY)) TExtractType<4> ywzy;
__declspec(property(get = YWZY, put = YWZY)) TExtractType<4> gabg;
TExtractType<4> YWZZ() const { return ExtractComponent<3, 1, 3, 2, 2>(); } 
template <spv::StorageClass C1> void YWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 2, 2>(_var);}
void YWZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZZ, put = YWZZ)) TExtractType<4> ywzz;
__declspec(property(get = YWZZ, put = YWZZ)) TExtractType<4> gabb;
TExtractType<4> YWZW() const { return ExtractComponent<3, 1, 3, 2, 3>(); } 
template <spv::StorageClass C1> void YWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 2, 3>(_var);}
void YWZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWZW, put = YWZW)) TExtractType<4> ywzw;
__declspec(property(get = YWZW, put = YWZW)) TExtractType<4> gaba;
TExtractType<3> YWW() const { return ExtractComponent<3, 1, 3, 3>(); } 
template <spv::StorageClass C1> void YWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 3>(_var);}
void YWW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWW, put = YWW)) TExtractType<3> yww;
__declspec(property(get = YWW, put = YWW)) TExtractType<3> gaa;
TExtractType<4> YWWX() const { return ExtractComponent<3, 1, 3, 3, 0>(); } 
template <spv::StorageClass C1> void YWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 3, 0>(_var);}
void YWWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWWX, put = YWWX)) TExtractType<4> ywwx;
__declspec(property(get = YWWX, put = YWWX)) TExtractType<4> gaar;
TExtractType<4> YWWY() const { return ExtractComponent<3, 1, 3, 3, 1>(); } 
template <spv::StorageClass C1> void YWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 3, 1>(_var);}
void YWWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWWY, put = YWWY)) TExtractType<4> ywwy;
__declspec(property(get = YWWY, put = YWWY)) TExtractType<4> gaag;
TExtractType<4> YWWZ() const { return ExtractComponent<3, 1, 3, 3, 2>(); } 
template <spv::StorageClass C1> void YWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 3, 2>(_var);}
void YWWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWWZ, put = YWWZ)) TExtractType<4> ywwz;
__declspec(property(get = YWWZ, put = YWWZ)) TExtractType<4> gaab;
TExtractType<4> YWWW() const { return ExtractComponent<3, 1, 3, 3, 3>(); } 
template <spv::StorageClass C1> void YWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 1, 3, 3, 3>(_var);}
void YWWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 1, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = YWWW, put = YWWW)) TExtractType<4> ywww;
__declspec(property(get = YWWW, put = YWWW)) TExtractType<4> gaaa;
TExtractType<1> Z() const { return ExtractComponent<1, 2>(); } 
template <spv::StorageClass C1> void Z(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) const { InsertComponent<1, 2>(_var);}
void Z(const vec_type_t<base_type_t<T>, 1>& _var) const { InsertComponent<1, 2>(var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = Z, put = Z)) TExtractType<1> z;
__declspec(property(get = Z, put = Z)) TExtractType<1> b;
TExtractType<2> ZX() const { return ExtractComponent<2, 2, 0>(); } 
template <spv::StorageClass C1> void ZX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 2, 0>(_var);}
void ZX(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZX, put = ZX)) TExtractType<2> zx;
__declspec(property(get = ZX, put = ZX)) TExtractType<2> br;
TExtractType<3> ZXX() const { return ExtractComponent<3, 2, 0, 0>(); } 
template <spv::StorageClass C1> void ZXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 0>(_var);}
void ZXX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXX, put = ZXX)) TExtractType<3> zxx;
__declspec(property(get = ZXX, put = ZXX)) TExtractType<3> brr;
TExtractType<4> ZXXX() const { return ExtractComponent<3, 2, 0, 0, 0>(); } 
template <spv::StorageClass C1> void ZXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 0, 0>(_var);}
void ZXXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXXX, put = ZXXX)) TExtractType<4> zxxx;
__declspec(property(get = ZXXX, put = ZXXX)) TExtractType<4> brrr;
TExtractType<4> ZXXY() const { return ExtractComponent<3, 2, 0, 0, 1>(); } 
template <spv::StorageClass C1> void ZXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 0, 1>(_var);}
void ZXXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXXY, put = ZXXY)) TExtractType<4> zxxy;
__declspec(property(get = ZXXY, put = ZXXY)) TExtractType<4> brrg;
TExtractType<4> ZXXZ() const { return ExtractComponent<3, 2, 0, 0, 2>(); } 
template <spv::StorageClass C1> void ZXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 0, 2>(_var);}
void ZXXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXXZ, put = ZXXZ)) TExtractType<4> zxxz;
__declspec(property(get = ZXXZ, put = ZXXZ)) TExtractType<4> brrb;
TExtractType<4> ZXXW() const { return ExtractComponent<3, 2, 0, 0, 3>(); } 
template <spv::StorageClass C1> void ZXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 0, 3>(_var);}
void ZXXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXXW, put = ZXXW)) TExtractType<4> zxxw;
__declspec(property(get = ZXXW, put = ZXXW)) TExtractType<4> brra;
TExtractType<3> ZXY() const { return ExtractComponent<3, 2, 0, 1>(); } 
template <spv::StorageClass C1> void ZXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 1>(_var);}
void ZXY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXY, put = ZXY)) TExtractType<3> zxy;
__declspec(property(get = ZXY, put = ZXY)) TExtractType<3> brg;
TExtractType<4> ZXYX() const { return ExtractComponent<3, 2, 0, 1, 0>(); } 
template <spv::StorageClass C1> void ZXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 1, 0>(_var);}
void ZXYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXYX, put = ZXYX)) TExtractType<4> zxyx;
__declspec(property(get = ZXYX, put = ZXYX)) TExtractType<4> brgr;
TExtractType<4> ZXYY() const { return ExtractComponent<3, 2, 0, 1, 1>(); } 
template <spv::StorageClass C1> void ZXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 1, 1>(_var);}
void ZXYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXYY, put = ZXYY)) TExtractType<4> zxyy;
__declspec(property(get = ZXYY, put = ZXYY)) TExtractType<4> brgg;
TExtractType<4> ZXYZ() const { return ExtractComponent<3, 2, 0, 1, 2>(); } 
template <spv::StorageClass C1> void ZXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 1, 2>(_var);}
void ZXYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXYZ, put = ZXYZ)) TExtractType<4> zxyz;
__declspec(property(get = ZXYZ, put = ZXYZ)) TExtractType<4> brgb;
TExtractType<4> ZXYW() const { return ExtractComponent<3, 2, 0, 1, 3>(); } 
template <spv::StorageClass C1> void ZXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 1, 3>(_var);}
void ZXYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXYW, put = ZXYW)) TExtractType<4> zxyw;
__declspec(property(get = ZXYW, put = ZXYW)) TExtractType<4> brga;
TExtractType<3> ZXZ() const { return ExtractComponent<3, 2, 0, 2>(); } 
template <spv::StorageClass C1> void ZXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 2>(_var);}
void ZXZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZ, put = ZXZ)) TExtractType<3> zxz;
__declspec(property(get = ZXZ, put = ZXZ)) TExtractType<3> brb;
TExtractType<4> ZXZX() const { return ExtractComponent<3, 2, 0, 2, 0>(); } 
template <spv::StorageClass C1> void ZXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 2, 0>(_var);}
void ZXZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZX, put = ZXZX)) TExtractType<4> zxzx;
__declspec(property(get = ZXZX, put = ZXZX)) TExtractType<4> brbr;
TExtractType<4> ZXZY() const { return ExtractComponent<3, 2, 0, 2, 1>(); } 
template <spv::StorageClass C1> void ZXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 2, 1>(_var);}
void ZXZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZY, put = ZXZY)) TExtractType<4> zxzy;
__declspec(property(get = ZXZY, put = ZXZY)) TExtractType<4> brbg;
TExtractType<4> ZXZZ() const { return ExtractComponent<3, 2, 0, 2, 2>(); } 
template <spv::StorageClass C1> void ZXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 2, 2>(_var);}
void ZXZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZZ, put = ZXZZ)) TExtractType<4> zxzz;
__declspec(property(get = ZXZZ, put = ZXZZ)) TExtractType<4> brbb;
TExtractType<4> ZXZW() const { return ExtractComponent<3, 2, 0, 2, 3>(); } 
template <spv::StorageClass C1> void ZXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 2, 3>(_var);}
void ZXZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXZW, put = ZXZW)) TExtractType<4> zxzw;
__declspec(property(get = ZXZW, put = ZXZW)) TExtractType<4> brba;
TExtractType<3> ZXW() const { return ExtractComponent<3, 2, 0, 3>(); } 
template <spv::StorageClass C1> void ZXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 3>(_var);}
void ZXW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXW, put = ZXW)) TExtractType<3> zxw;
__declspec(property(get = ZXW, put = ZXW)) TExtractType<3> bra;
TExtractType<4> ZXWX() const { return ExtractComponent<3, 2, 0, 3, 0>(); } 
template <spv::StorageClass C1> void ZXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 3, 0>(_var);}
void ZXWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXWX, put = ZXWX)) TExtractType<4> zxwx;
__declspec(property(get = ZXWX, put = ZXWX)) TExtractType<4> brar;
TExtractType<4> ZXWY() const { return ExtractComponent<3, 2, 0, 3, 1>(); } 
template <spv::StorageClass C1> void ZXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 3, 1>(_var);}
void ZXWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXWY, put = ZXWY)) TExtractType<4> zxwy;
__declspec(property(get = ZXWY, put = ZXWY)) TExtractType<4> brag;
TExtractType<4> ZXWZ() const { return ExtractComponent<3, 2, 0, 3, 2>(); } 
template <spv::StorageClass C1> void ZXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 3, 2>(_var);}
void ZXWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXWZ, put = ZXWZ)) TExtractType<4> zxwz;
__declspec(property(get = ZXWZ, put = ZXWZ)) TExtractType<4> brab;
TExtractType<4> ZXWW() const { return ExtractComponent<3, 2, 0, 3, 3>(); } 
template <spv::StorageClass C1> void ZXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 0, 3, 3>(_var);}
void ZXWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZXWW, put = ZXWW)) TExtractType<4> zxww;
__declspec(property(get = ZXWW, put = ZXWW)) TExtractType<4> braa;
TExtractType<2> ZY() const { return ExtractComponent<2, 2, 1>(); } 
template <spv::StorageClass C1> void ZY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 2, 1>(_var);}
void ZY(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZY, put = ZY)) TExtractType<2> zy;
__declspec(property(get = ZY, put = ZY)) TExtractType<2> bg;
TExtractType<3> ZYX() const { return ExtractComponent<3, 2, 1, 0>(); } 
template <spv::StorageClass C1> void ZYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 0>(_var);}
void ZYX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYX, put = ZYX)) TExtractType<3> zyx;
__declspec(property(get = ZYX, put = ZYX)) TExtractType<3> bgr;
TExtractType<4> ZYXX() const { return ExtractComponent<3, 2, 1, 0, 0>(); } 
template <spv::StorageClass C1> void ZYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 0, 0>(_var);}
void ZYXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYXX, put = ZYXX)) TExtractType<4> zyxx;
__declspec(property(get = ZYXX, put = ZYXX)) TExtractType<4> bgrr;
TExtractType<4> ZYXY() const { return ExtractComponent<3, 2, 1, 0, 1>(); } 
template <spv::StorageClass C1> void ZYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 0, 1>(_var);}
void ZYXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYXY, put = ZYXY)) TExtractType<4> zyxy;
__declspec(property(get = ZYXY, put = ZYXY)) TExtractType<4> bgrg;
TExtractType<4> ZYXZ() const { return ExtractComponent<3, 2, 1, 0, 2>(); } 
template <spv::StorageClass C1> void ZYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 0, 2>(_var);}
void ZYXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYXZ, put = ZYXZ)) TExtractType<4> zyxz;
__declspec(property(get = ZYXZ, put = ZYXZ)) TExtractType<4> bgrb;
TExtractType<4> ZYXW() const { return ExtractComponent<3, 2, 1, 0, 3>(); } 
template <spv::StorageClass C1> void ZYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 0, 3>(_var);}
void ZYXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYXW, put = ZYXW)) TExtractType<4> zyxw;
__declspec(property(get = ZYXW, put = ZYXW)) TExtractType<4> bgra;
TExtractType<3> ZYY() const { return ExtractComponent<3, 2, 1, 1>(); } 
template <spv::StorageClass C1> void ZYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 1>(_var);}
void ZYY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYY, put = ZYY)) TExtractType<3> zyy;
__declspec(property(get = ZYY, put = ZYY)) TExtractType<3> bgg;
TExtractType<4> ZYYX() const { return ExtractComponent<3, 2, 1, 1, 0>(); } 
template <spv::StorageClass C1> void ZYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 1, 0>(_var);}
void ZYYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYYX, put = ZYYX)) TExtractType<4> zyyx;
__declspec(property(get = ZYYX, put = ZYYX)) TExtractType<4> bggr;
TExtractType<4> ZYYY() const { return ExtractComponent<3, 2, 1, 1, 1>(); } 
template <spv::StorageClass C1> void ZYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 1, 1>(_var);}
void ZYYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYYY, put = ZYYY)) TExtractType<4> zyyy;
__declspec(property(get = ZYYY, put = ZYYY)) TExtractType<4> bggg;
TExtractType<4> ZYYZ() const { return ExtractComponent<3, 2, 1, 1, 2>(); } 
template <spv::StorageClass C1> void ZYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 1, 2>(_var);}
void ZYYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYYZ, put = ZYYZ)) TExtractType<4> zyyz;
__declspec(property(get = ZYYZ, put = ZYYZ)) TExtractType<4> bggb;
TExtractType<4> ZYYW() const { return ExtractComponent<3, 2, 1, 1, 3>(); } 
template <spv::StorageClass C1> void ZYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 1, 3>(_var);}
void ZYYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYYW, put = ZYYW)) TExtractType<4> zyyw;
__declspec(property(get = ZYYW, put = ZYYW)) TExtractType<4> bgga;
TExtractType<3> ZYZ() const { return ExtractComponent<3, 2, 1, 2>(); } 
template <spv::StorageClass C1> void ZYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 2>(_var);}
void ZYZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZ, put = ZYZ)) TExtractType<3> zyz;
__declspec(property(get = ZYZ, put = ZYZ)) TExtractType<3> bgb;
TExtractType<4> ZYZX() const { return ExtractComponent<3, 2, 1, 2, 0>(); } 
template <spv::StorageClass C1> void ZYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 2, 0>(_var);}
void ZYZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZX, put = ZYZX)) TExtractType<4> zyzx;
__declspec(property(get = ZYZX, put = ZYZX)) TExtractType<4> bgbr;
TExtractType<4> ZYZY() const { return ExtractComponent<3, 2, 1, 2, 1>(); } 
template <spv::StorageClass C1> void ZYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 2, 1>(_var);}
void ZYZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZY, put = ZYZY)) TExtractType<4> zyzy;
__declspec(property(get = ZYZY, put = ZYZY)) TExtractType<4> bgbg;
TExtractType<4> ZYZZ() const { return ExtractComponent<3, 2, 1, 2, 2>(); } 
template <spv::StorageClass C1> void ZYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 2, 2>(_var);}
void ZYZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZZ, put = ZYZZ)) TExtractType<4> zyzz;
__declspec(property(get = ZYZZ, put = ZYZZ)) TExtractType<4> bgbb;
TExtractType<4> ZYZW() const { return ExtractComponent<3, 2, 1, 2, 3>(); } 
template <spv::StorageClass C1> void ZYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 2, 3>(_var);}
void ZYZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYZW, put = ZYZW)) TExtractType<4> zyzw;
__declspec(property(get = ZYZW, put = ZYZW)) TExtractType<4> bgba;
TExtractType<3> ZYW() const { return ExtractComponent<3, 2, 1, 3>(); } 
template <spv::StorageClass C1> void ZYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 3>(_var);}
void ZYW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYW, put = ZYW)) TExtractType<3> zyw;
__declspec(property(get = ZYW, put = ZYW)) TExtractType<3> bga;
TExtractType<4> ZYWX() const { return ExtractComponent<3, 2, 1, 3, 0>(); } 
template <spv::StorageClass C1> void ZYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 3, 0>(_var);}
void ZYWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYWX, put = ZYWX)) TExtractType<4> zywx;
__declspec(property(get = ZYWX, put = ZYWX)) TExtractType<4> bgar;
TExtractType<4> ZYWY() const { return ExtractComponent<3, 2, 1, 3, 1>(); } 
template <spv::StorageClass C1> void ZYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 3, 1>(_var);}
void ZYWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYWY, put = ZYWY)) TExtractType<4> zywy;
__declspec(property(get = ZYWY, put = ZYWY)) TExtractType<4> bgag;
TExtractType<4> ZYWZ() const { return ExtractComponent<3, 2, 1, 3, 2>(); } 
template <spv::StorageClass C1> void ZYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 3, 2>(_var);}
void ZYWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYWZ, put = ZYWZ)) TExtractType<4> zywz;
__declspec(property(get = ZYWZ, put = ZYWZ)) TExtractType<4> bgab;
TExtractType<4> ZYWW() const { return ExtractComponent<3, 2, 1, 3, 3>(); } 
template <spv::StorageClass C1> void ZYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 1, 3, 3>(_var);}
void ZYWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZYWW, put = ZYWW)) TExtractType<4> zyww;
__declspec(property(get = ZYWW, put = ZYWW)) TExtractType<4> bgaa;
TExtractType<2> ZZ() const { return ExtractComponent<2, 2, 2>(); } 
template <spv::StorageClass C1> void ZZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 2, 2>(_var);}
void ZZ(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZ, put = ZZ)) TExtractType<2> zz;
__declspec(property(get = ZZ, put = ZZ)) TExtractType<2> bb;
TExtractType<3> ZZX() const { return ExtractComponent<3, 2, 2, 0>(); } 
template <spv::StorageClass C1> void ZZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 0>(_var);}
void ZZX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZX, put = ZZX)) TExtractType<3> zzx;
__declspec(property(get = ZZX, put = ZZX)) TExtractType<3> bbr;
TExtractType<4> ZZXX() const { return ExtractComponent<3, 2, 2, 0, 0>(); } 
template <spv::StorageClass C1> void ZZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 0, 0>(_var);}
void ZZXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZXX, put = ZZXX)) TExtractType<4> zzxx;
__declspec(property(get = ZZXX, put = ZZXX)) TExtractType<4> bbrr;
TExtractType<4> ZZXY() const { return ExtractComponent<3, 2, 2, 0, 1>(); } 
template <spv::StorageClass C1> void ZZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 0, 1>(_var);}
void ZZXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZXY, put = ZZXY)) TExtractType<4> zzxy;
__declspec(property(get = ZZXY, put = ZZXY)) TExtractType<4> bbrg;
TExtractType<4> ZZXZ() const { return ExtractComponent<3, 2, 2, 0, 2>(); } 
template <spv::StorageClass C1> void ZZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 0, 2>(_var);}
void ZZXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZXZ, put = ZZXZ)) TExtractType<4> zzxz;
__declspec(property(get = ZZXZ, put = ZZXZ)) TExtractType<4> bbrb;
TExtractType<4> ZZXW() const { return ExtractComponent<3, 2, 2, 0, 3>(); } 
template <spv::StorageClass C1> void ZZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 0, 3>(_var);}
void ZZXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZXW, put = ZZXW)) TExtractType<4> zzxw;
__declspec(property(get = ZZXW, put = ZZXW)) TExtractType<4> bbra;
TExtractType<3> ZZY() const { return ExtractComponent<3, 2, 2, 1>(); } 
template <spv::StorageClass C1> void ZZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 1>(_var);}
void ZZY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZY, put = ZZY)) TExtractType<3> zzy;
__declspec(property(get = ZZY, put = ZZY)) TExtractType<3> bbg;
TExtractType<4> ZZYX() const { return ExtractComponent<3, 2, 2, 1, 0>(); } 
template <spv::StorageClass C1> void ZZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 1, 0>(_var);}
void ZZYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZYX, put = ZZYX)) TExtractType<4> zzyx;
__declspec(property(get = ZZYX, put = ZZYX)) TExtractType<4> bbgr;
TExtractType<4> ZZYY() const { return ExtractComponent<3, 2, 2, 1, 1>(); } 
template <spv::StorageClass C1> void ZZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 1, 1>(_var);}
void ZZYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZYY, put = ZZYY)) TExtractType<4> zzyy;
__declspec(property(get = ZZYY, put = ZZYY)) TExtractType<4> bbgg;
TExtractType<4> ZZYZ() const { return ExtractComponent<3, 2, 2, 1, 2>(); } 
template <spv::StorageClass C1> void ZZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 1, 2>(_var);}
void ZZYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZYZ, put = ZZYZ)) TExtractType<4> zzyz;
__declspec(property(get = ZZYZ, put = ZZYZ)) TExtractType<4> bbgb;
TExtractType<4> ZZYW() const { return ExtractComponent<3, 2, 2, 1, 3>(); } 
template <spv::StorageClass C1> void ZZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 1, 3>(_var);}
void ZZYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZYW, put = ZZYW)) TExtractType<4> zzyw;
__declspec(property(get = ZZYW, put = ZZYW)) TExtractType<4> bbga;
TExtractType<3> ZZZ() const { return ExtractComponent<3, 2, 2, 2>(); } 
template <spv::StorageClass C1> void ZZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 2>(_var);}
void ZZZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZ, put = ZZZ)) TExtractType<3> zzz;
__declspec(property(get = ZZZ, put = ZZZ)) TExtractType<3> bbb;
TExtractType<4> ZZZX() const { return ExtractComponent<3, 2, 2, 2, 0>(); } 
template <spv::StorageClass C1> void ZZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 2, 0>(_var);}
void ZZZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZX, put = ZZZX)) TExtractType<4> zzzx;
__declspec(property(get = ZZZX, put = ZZZX)) TExtractType<4> bbbr;
TExtractType<4> ZZZY() const { return ExtractComponent<3, 2, 2, 2, 1>(); } 
template <spv::StorageClass C1> void ZZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 2, 1>(_var);}
void ZZZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZY, put = ZZZY)) TExtractType<4> zzzy;
__declspec(property(get = ZZZY, put = ZZZY)) TExtractType<4> bbbg;
TExtractType<4> ZZZZ() const { return ExtractComponent<3, 2, 2, 2, 2>(); } 
template <spv::StorageClass C1> void ZZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 2, 2>(_var);}
void ZZZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZZ, put = ZZZZ)) TExtractType<4> zzzz;
__declspec(property(get = ZZZZ, put = ZZZZ)) TExtractType<4> bbbb;
TExtractType<4> ZZZW() const { return ExtractComponent<3, 2, 2, 2, 3>(); } 
template <spv::StorageClass C1> void ZZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 2, 3>(_var);}
void ZZZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZZW, put = ZZZW)) TExtractType<4> zzzw;
__declspec(property(get = ZZZW, put = ZZZW)) TExtractType<4> bbba;
TExtractType<3> ZZW() const { return ExtractComponent<3, 2, 2, 3>(); } 
template <spv::StorageClass C1> void ZZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 3>(_var);}
void ZZW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZW, put = ZZW)) TExtractType<3> zzw;
__declspec(property(get = ZZW, put = ZZW)) TExtractType<3> bba;
TExtractType<4> ZZWX() const { return ExtractComponent<3, 2, 2, 3, 0>(); } 
template <spv::StorageClass C1> void ZZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 3, 0>(_var);}
void ZZWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZWX, put = ZZWX)) TExtractType<4> zzwx;
__declspec(property(get = ZZWX, put = ZZWX)) TExtractType<4> bbar;
TExtractType<4> ZZWY() const { return ExtractComponent<3, 2, 2, 3, 1>(); } 
template <spv::StorageClass C1> void ZZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 3, 1>(_var);}
void ZZWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZWY, put = ZZWY)) TExtractType<4> zzwy;
__declspec(property(get = ZZWY, put = ZZWY)) TExtractType<4> bbag;
TExtractType<4> ZZWZ() const { return ExtractComponent<3, 2, 2, 3, 2>(); } 
template <spv::StorageClass C1> void ZZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 3, 2>(_var);}
void ZZWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZWZ, put = ZZWZ)) TExtractType<4> zzwz;
__declspec(property(get = ZZWZ, put = ZZWZ)) TExtractType<4> bbab;
TExtractType<4> ZZWW() const { return ExtractComponent<3, 2, 2, 3, 3>(); } 
template <spv::StorageClass C1> void ZZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 2, 3, 3>(_var);}
void ZZWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZZWW, put = ZZWW)) TExtractType<4> zzww;
__declspec(property(get = ZZWW, put = ZZWW)) TExtractType<4> bbaa;
TExtractType<2> ZW() const { return ExtractComponent<2, 2, 3>(); } 
template <spv::StorageClass C1> void ZW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 2, 3>(_var);}
void ZW(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZW, put = ZW)) TExtractType<2> zw;
__declspec(property(get = ZW, put = ZW)) TExtractType<2> ba;
TExtractType<3> ZWX() const { return ExtractComponent<3, 2, 3, 0>(); } 
template <spv::StorageClass C1> void ZWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 0>(_var);}
void ZWX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWX, put = ZWX)) TExtractType<3> zwx;
__declspec(property(get = ZWX, put = ZWX)) TExtractType<3> bar;
TExtractType<4> ZWXX() const { return ExtractComponent<3, 2, 3, 0, 0>(); } 
template <spv::StorageClass C1> void ZWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 0, 0>(_var);}
void ZWXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWXX, put = ZWXX)) TExtractType<4> zwxx;
__declspec(property(get = ZWXX, put = ZWXX)) TExtractType<4> barr;
TExtractType<4> ZWXY() const { return ExtractComponent<3, 2, 3, 0, 1>(); } 
template <spv::StorageClass C1> void ZWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 0, 1>(_var);}
void ZWXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWXY, put = ZWXY)) TExtractType<4> zwxy;
__declspec(property(get = ZWXY, put = ZWXY)) TExtractType<4> barg;
TExtractType<4> ZWXZ() const { return ExtractComponent<3, 2, 3, 0, 2>(); } 
template <spv::StorageClass C1> void ZWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 0, 2>(_var);}
void ZWXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWXZ, put = ZWXZ)) TExtractType<4> zwxz;
__declspec(property(get = ZWXZ, put = ZWXZ)) TExtractType<4> barb;
TExtractType<4> ZWXW() const { return ExtractComponent<3, 2, 3, 0, 3>(); } 
template <spv::StorageClass C1> void ZWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 0, 3>(_var);}
void ZWXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWXW, put = ZWXW)) TExtractType<4> zwxw;
__declspec(property(get = ZWXW, put = ZWXW)) TExtractType<4> bara;
TExtractType<3> ZWY() const { return ExtractComponent<3, 2, 3, 1>(); } 
template <spv::StorageClass C1> void ZWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 1>(_var);}
void ZWY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWY, put = ZWY)) TExtractType<3> zwy;
__declspec(property(get = ZWY, put = ZWY)) TExtractType<3> bag;
TExtractType<4> ZWYX() const { return ExtractComponent<3, 2, 3, 1, 0>(); } 
template <spv::StorageClass C1> void ZWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 1, 0>(_var);}
void ZWYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWYX, put = ZWYX)) TExtractType<4> zwyx;
__declspec(property(get = ZWYX, put = ZWYX)) TExtractType<4> bagr;
TExtractType<4> ZWYY() const { return ExtractComponent<3, 2, 3, 1, 1>(); } 
template <spv::StorageClass C1> void ZWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 1, 1>(_var);}
void ZWYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWYY, put = ZWYY)) TExtractType<4> zwyy;
__declspec(property(get = ZWYY, put = ZWYY)) TExtractType<4> bagg;
TExtractType<4> ZWYZ() const { return ExtractComponent<3, 2, 3, 1, 2>(); } 
template <spv::StorageClass C1> void ZWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 1, 2>(_var);}
void ZWYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWYZ, put = ZWYZ)) TExtractType<4> zwyz;
__declspec(property(get = ZWYZ, put = ZWYZ)) TExtractType<4> bagb;
TExtractType<4> ZWYW() const { return ExtractComponent<3, 2, 3, 1, 3>(); } 
template <spv::StorageClass C1> void ZWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 1, 3>(_var);}
void ZWYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWYW, put = ZWYW)) TExtractType<4> zwyw;
__declspec(property(get = ZWYW, put = ZWYW)) TExtractType<4> baga;
TExtractType<3> ZWZ() const { return ExtractComponent<3, 2, 3, 2>(); } 
template <spv::StorageClass C1> void ZWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 2>(_var);}
void ZWZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZ, put = ZWZ)) TExtractType<3> zwz;
__declspec(property(get = ZWZ, put = ZWZ)) TExtractType<3> bab;
TExtractType<4> ZWZX() const { return ExtractComponent<3, 2, 3, 2, 0>(); } 
template <spv::StorageClass C1> void ZWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 2, 0>(_var);}
void ZWZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZX, put = ZWZX)) TExtractType<4> zwzx;
__declspec(property(get = ZWZX, put = ZWZX)) TExtractType<4> babr;
TExtractType<4> ZWZY() const { return ExtractComponent<3, 2, 3, 2, 1>(); } 
template <spv::StorageClass C1> void ZWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 2, 1>(_var);}
void ZWZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZY, put = ZWZY)) TExtractType<4> zwzy;
__declspec(property(get = ZWZY, put = ZWZY)) TExtractType<4> babg;
TExtractType<4> ZWZZ() const { return ExtractComponent<3, 2, 3, 2, 2>(); } 
template <spv::StorageClass C1> void ZWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 2, 2>(_var);}
void ZWZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZZ, put = ZWZZ)) TExtractType<4> zwzz;
__declspec(property(get = ZWZZ, put = ZWZZ)) TExtractType<4> babb;
TExtractType<4> ZWZW() const { return ExtractComponent<3, 2, 3, 2, 3>(); } 
template <spv::StorageClass C1> void ZWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 2, 3>(_var);}
void ZWZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWZW, put = ZWZW)) TExtractType<4> zwzw;
__declspec(property(get = ZWZW, put = ZWZW)) TExtractType<4> baba;
TExtractType<3> ZWW() const { return ExtractComponent<3, 2, 3, 3>(); } 
template <spv::StorageClass C1> void ZWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 3>(_var);}
void ZWW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWW, put = ZWW)) TExtractType<3> zww;
__declspec(property(get = ZWW, put = ZWW)) TExtractType<3> baa;
TExtractType<4> ZWWX() const { return ExtractComponent<3, 2, 3, 3, 0>(); } 
template <spv::StorageClass C1> void ZWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 3, 0>(_var);}
void ZWWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWWX, put = ZWWX)) TExtractType<4> zwwx;
__declspec(property(get = ZWWX, put = ZWWX)) TExtractType<4> baar;
TExtractType<4> ZWWY() const { return ExtractComponent<3, 2, 3, 3, 1>(); } 
template <spv::StorageClass C1> void ZWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 3, 1>(_var);}
void ZWWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWWY, put = ZWWY)) TExtractType<4> zwwy;
__declspec(property(get = ZWWY, put = ZWWY)) TExtractType<4> baag;
TExtractType<4> ZWWZ() const { return ExtractComponent<3, 2, 3, 3, 2>(); } 
template <spv::StorageClass C1> void ZWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 3, 2>(_var);}
void ZWWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWWZ, put = ZWWZ)) TExtractType<4> zwwz;
__declspec(property(get = ZWWZ, put = ZWWZ)) TExtractType<4> baab;
TExtractType<4> ZWWW() const { return ExtractComponent<3, 2, 3, 3, 3>(); } 
template <spv::StorageClass C1> void ZWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 2, 3, 3, 3>(_var);}
void ZWWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 2, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = ZWWW, put = ZWWW)) TExtractType<4> zwww;
__declspec(property(get = ZWWW, put = ZWWW)) TExtractType<4> baaa;
TExtractType<1> W() const { return ExtractComponent<1, 3>(); } 
template <spv::StorageClass C1> void W(const var_t<vec_type_t<base_type_t<T>, 1>, Assemble, C1>& _var) const { InsertComponent<1, 3>(_var);}
void W(const vec_type_t<base_type_t<T>, 1>& _var) const { InsertComponent<1, 3>(var_t<vec_type_t<base_type_t<T>, 1>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = W, put = W)) TExtractType<1> w;
__declspec(property(get = W, put = W)) TExtractType<1> a;
TExtractType<2> WX() const { return ExtractComponent<2, 3, 0>(); } 
template <spv::StorageClass C1> void WX(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 3, 0>(_var);}
void WX(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WX, put = WX)) TExtractType<2> wx;
__declspec(property(get = WX, put = WX)) TExtractType<2> ar;
TExtractType<3> WXX() const { return ExtractComponent<3, 3, 0, 0>(); } 
template <spv::StorageClass C1> void WXX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 0>(_var);}
void WXX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXX, put = WXX)) TExtractType<3> wxx;
__declspec(property(get = WXX, put = WXX)) TExtractType<3> arr;
TExtractType<4> WXXX() const { return ExtractComponent<3, 3, 0, 0, 0>(); } 
template <spv::StorageClass C1> void WXXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 0, 0>(_var);}
void WXXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXXX, put = WXXX)) TExtractType<4> wxxx;
__declspec(property(get = WXXX, put = WXXX)) TExtractType<4> arrr;
TExtractType<4> WXXY() const { return ExtractComponent<3, 3, 0, 0, 1>(); } 
template <spv::StorageClass C1> void WXXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 0, 1>(_var);}
void WXXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXXY, put = WXXY)) TExtractType<4> wxxy;
__declspec(property(get = WXXY, put = WXXY)) TExtractType<4> arrg;
TExtractType<4> WXXZ() const { return ExtractComponent<3, 3, 0, 0, 2>(); } 
template <spv::StorageClass C1> void WXXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 0, 2>(_var);}
void WXXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXXZ, put = WXXZ)) TExtractType<4> wxxz;
__declspec(property(get = WXXZ, put = WXXZ)) TExtractType<4> arrb;
TExtractType<4> WXXW() const { return ExtractComponent<3, 3, 0, 0, 3>(); } 
template <spv::StorageClass C1> void WXXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 0, 3>(_var);}
void WXXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXXW, put = WXXW)) TExtractType<4> wxxw;
__declspec(property(get = WXXW, put = WXXW)) TExtractType<4> arra;
TExtractType<3> WXY() const { return ExtractComponent<3, 3, 0, 1>(); } 
template <spv::StorageClass C1> void WXY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 1>(_var);}
void WXY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXY, put = WXY)) TExtractType<3> wxy;
__declspec(property(get = WXY, put = WXY)) TExtractType<3> arg;
TExtractType<4> WXYX() const { return ExtractComponent<3, 3, 0, 1, 0>(); } 
template <spv::StorageClass C1> void WXYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 1, 0>(_var);}
void WXYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXYX, put = WXYX)) TExtractType<4> wxyx;
__declspec(property(get = WXYX, put = WXYX)) TExtractType<4> argr;
TExtractType<4> WXYY() const { return ExtractComponent<3, 3, 0, 1, 1>(); } 
template <spv::StorageClass C1> void WXYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 1, 1>(_var);}
void WXYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXYY, put = WXYY)) TExtractType<4> wxyy;
__declspec(property(get = WXYY, put = WXYY)) TExtractType<4> argg;
TExtractType<4> WXYZ() const { return ExtractComponent<3, 3, 0, 1, 2>(); } 
template <spv::StorageClass C1> void WXYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 1, 2>(_var);}
void WXYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXYZ, put = WXYZ)) TExtractType<4> wxyz;
__declspec(property(get = WXYZ, put = WXYZ)) TExtractType<4> argb;
TExtractType<4> WXYW() const { return ExtractComponent<3, 3, 0, 1, 3>(); } 
template <spv::StorageClass C1> void WXYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 1, 3>(_var);}
void WXYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXYW, put = WXYW)) TExtractType<4> wxyw;
__declspec(property(get = WXYW, put = WXYW)) TExtractType<4> arga;
TExtractType<3> WXZ() const { return ExtractComponent<3, 3, 0, 2>(); } 
template <spv::StorageClass C1> void WXZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 2>(_var);}
void WXZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZ, put = WXZ)) TExtractType<3> wxz;
__declspec(property(get = WXZ, put = WXZ)) TExtractType<3> arb;
TExtractType<4> WXZX() const { return ExtractComponent<3, 3, 0, 2, 0>(); } 
template <spv::StorageClass C1> void WXZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 2, 0>(_var);}
void WXZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZX, put = WXZX)) TExtractType<4> wxzx;
__declspec(property(get = WXZX, put = WXZX)) TExtractType<4> arbr;
TExtractType<4> WXZY() const { return ExtractComponent<3, 3, 0, 2, 1>(); } 
template <spv::StorageClass C1> void WXZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 2, 1>(_var);}
void WXZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZY, put = WXZY)) TExtractType<4> wxzy;
__declspec(property(get = WXZY, put = WXZY)) TExtractType<4> arbg;
TExtractType<4> WXZZ() const { return ExtractComponent<3, 3, 0, 2, 2>(); } 
template <spv::StorageClass C1> void WXZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 2, 2>(_var);}
void WXZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZZ, put = WXZZ)) TExtractType<4> wxzz;
__declspec(property(get = WXZZ, put = WXZZ)) TExtractType<4> arbb;
TExtractType<4> WXZW() const { return ExtractComponent<3, 3, 0, 2, 3>(); } 
template <spv::StorageClass C1> void WXZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 2, 3>(_var);}
void WXZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXZW, put = WXZW)) TExtractType<4> wxzw;
__declspec(property(get = WXZW, put = WXZW)) TExtractType<4> arba;
TExtractType<3> WXW() const { return ExtractComponent<3, 3, 0, 3>(); } 
template <spv::StorageClass C1> void WXW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 3>(_var);}
void WXW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXW, put = WXW)) TExtractType<3> wxw;
__declspec(property(get = WXW, put = WXW)) TExtractType<3> ara;
TExtractType<4> WXWX() const { return ExtractComponent<3, 3, 0, 3, 0>(); } 
template <spv::StorageClass C1> void WXWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 3, 0>(_var);}
void WXWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXWX, put = WXWX)) TExtractType<4> wxwx;
__declspec(property(get = WXWX, put = WXWX)) TExtractType<4> arar;
TExtractType<4> WXWY() const { return ExtractComponent<3, 3, 0, 3, 1>(); } 
template <spv::StorageClass C1> void WXWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 3, 1>(_var);}
void WXWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXWY, put = WXWY)) TExtractType<4> wxwy;
__declspec(property(get = WXWY, put = WXWY)) TExtractType<4> arag;
TExtractType<4> WXWZ() const { return ExtractComponent<3, 3, 0, 3, 2>(); } 
template <spv::StorageClass C1> void WXWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 3, 2>(_var);}
void WXWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXWZ, put = WXWZ)) TExtractType<4> wxwz;
__declspec(property(get = WXWZ, put = WXWZ)) TExtractType<4> arab;
TExtractType<4> WXWW() const { return ExtractComponent<3, 3, 0, 3, 3>(); } 
template <spv::StorageClass C1> void WXWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 0, 3, 3>(_var);}
void WXWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 0, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WXWW, put = WXWW)) TExtractType<4> wxww;
__declspec(property(get = WXWW, put = WXWW)) TExtractType<4> araa;
TExtractType<2> WY() const { return ExtractComponent<2, 3, 1>(); } 
template <spv::StorageClass C1> void WY(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 3, 1>(_var);}
void WY(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WY, put = WY)) TExtractType<2> wy;
__declspec(property(get = WY, put = WY)) TExtractType<2> ag;
TExtractType<3> WYX() const { return ExtractComponent<3, 3, 1, 0>(); } 
template <spv::StorageClass C1> void WYX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 0>(_var);}
void WYX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYX, put = WYX)) TExtractType<3> wyx;
__declspec(property(get = WYX, put = WYX)) TExtractType<3> agr;
TExtractType<4> WYXX() const { return ExtractComponent<3, 3, 1, 0, 0>(); } 
template <spv::StorageClass C1> void WYXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 0, 0>(_var);}
void WYXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYXX, put = WYXX)) TExtractType<4> wyxx;
__declspec(property(get = WYXX, put = WYXX)) TExtractType<4> agrr;
TExtractType<4> WYXY() const { return ExtractComponent<3, 3, 1, 0, 1>(); } 
template <spv::StorageClass C1> void WYXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 0, 1>(_var);}
void WYXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYXY, put = WYXY)) TExtractType<4> wyxy;
__declspec(property(get = WYXY, put = WYXY)) TExtractType<4> agrg;
TExtractType<4> WYXZ() const { return ExtractComponent<3, 3, 1, 0, 2>(); } 
template <spv::StorageClass C1> void WYXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 0, 2>(_var);}
void WYXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYXZ, put = WYXZ)) TExtractType<4> wyxz;
__declspec(property(get = WYXZ, put = WYXZ)) TExtractType<4> agrb;
TExtractType<4> WYXW() const { return ExtractComponent<3, 3, 1, 0, 3>(); } 
template <spv::StorageClass C1> void WYXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 0, 3>(_var);}
void WYXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYXW, put = WYXW)) TExtractType<4> wyxw;
__declspec(property(get = WYXW, put = WYXW)) TExtractType<4> agra;
TExtractType<3> WYY() const { return ExtractComponent<3, 3, 1, 1>(); } 
template <spv::StorageClass C1> void WYY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 1>(_var);}
void WYY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYY, put = WYY)) TExtractType<3> wyy;
__declspec(property(get = WYY, put = WYY)) TExtractType<3> agg;
TExtractType<4> WYYX() const { return ExtractComponent<3, 3, 1, 1, 0>(); } 
template <spv::StorageClass C1> void WYYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 1, 0>(_var);}
void WYYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYYX, put = WYYX)) TExtractType<4> wyyx;
__declspec(property(get = WYYX, put = WYYX)) TExtractType<4> aggr;
TExtractType<4> WYYY() const { return ExtractComponent<3, 3, 1, 1, 1>(); } 
template <spv::StorageClass C1> void WYYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 1, 1>(_var);}
void WYYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYYY, put = WYYY)) TExtractType<4> wyyy;
__declspec(property(get = WYYY, put = WYYY)) TExtractType<4> aggg;
TExtractType<4> WYYZ() const { return ExtractComponent<3, 3, 1, 1, 2>(); } 
template <spv::StorageClass C1> void WYYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 1, 2>(_var);}
void WYYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYYZ, put = WYYZ)) TExtractType<4> wyyz;
__declspec(property(get = WYYZ, put = WYYZ)) TExtractType<4> aggb;
TExtractType<4> WYYW() const { return ExtractComponent<3, 3, 1, 1, 3>(); } 
template <spv::StorageClass C1> void WYYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 1, 3>(_var);}
void WYYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYYW, put = WYYW)) TExtractType<4> wyyw;
__declspec(property(get = WYYW, put = WYYW)) TExtractType<4> agga;
TExtractType<3> WYZ() const { return ExtractComponent<3, 3, 1, 2>(); } 
template <spv::StorageClass C1> void WYZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 2>(_var);}
void WYZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZ, put = WYZ)) TExtractType<3> wyz;
__declspec(property(get = WYZ, put = WYZ)) TExtractType<3> agb;
TExtractType<4> WYZX() const { return ExtractComponent<3, 3, 1, 2, 0>(); } 
template <spv::StorageClass C1> void WYZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 2, 0>(_var);}
void WYZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZX, put = WYZX)) TExtractType<4> wyzx;
__declspec(property(get = WYZX, put = WYZX)) TExtractType<4> agbr;
TExtractType<4> WYZY() const { return ExtractComponent<3, 3, 1, 2, 1>(); } 
template <spv::StorageClass C1> void WYZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 2, 1>(_var);}
void WYZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZY, put = WYZY)) TExtractType<4> wyzy;
__declspec(property(get = WYZY, put = WYZY)) TExtractType<4> agbg;
TExtractType<4> WYZZ() const { return ExtractComponent<3, 3, 1, 2, 2>(); } 
template <spv::StorageClass C1> void WYZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 2, 2>(_var);}
void WYZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZZ, put = WYZZ)) TExtractType<4> wyzz;
__declspec(property(get = WYZZ, put = WYZZ)) TExtractType<4> agbb;
TExtractType<4> WYZW() const { return ExtractComponent<3, 3, 1, 2, 3>(); } 
template <spv::StorageClass C1> void WYZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 2, 3>(_var);}
void WYZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYZW, put = WYZW)) TExtractType<4> wyzw;
__declspec(property(get = WYZW, put = WYZW)) TExtractType<4> agba;
TExtractType<3> WYW() const { return ExtractComponent<3, 3, 1, 3>(); } 
template <spv::StorageClass C1> void WYW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 3>(_var);}
void WYW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYW, put = WYW)) TExtractType<3> wyw;
__declspec(property(get = WYW, put = WYW)) TExtractType<3> aga;
TExtractType<4> WYWX() const { return ExtractComponent<3, 3, 1, 3, 0>(); } 
template <spv::StorageClass C1> void WYWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 3, 0>(_var);}
void WYWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYWX, put = WYWX)) TExtractType<4> wywx;
__declspec(property(get = WYWX, put = WYWX)) TExtractType<4> agar;
TExtractType<4> WYWY() const { return ExtractComponent<3, 3, 1, 3, 1>(); } 
template <spv::StorageClass C1> void WYWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 3, 1>(_var);}
void WYWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYWY, put = WYWY)) TExtractType<4> wywy;
__declspec(property(get = WYWY, put = WYWY)) TExtractType<4> agag;
TExtractType<4> WYWZ() const { return ExtractComponent<3, 3, 1, 3, 2>(); } 
template <spv::StorageClass C1> void WYWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 3, 2>(_var);}
void WYWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYWZ, put = WYWZ)) TExtractType<4> wywz;
__declspec(property(get = WYWZ, put = WYWZ)) TExtractType<4> agab;
TExtractType<4> WYWW() const { return ExtractComponent<3, 3, 1, 3, 3>(); } 
template <spv::StorageClass C1> void WYWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 1, 3, 3>(_var);}
void WYWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 1, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WYWW, put = WYWW)) TExtractType<4> wyww;
__declspec(property(get = WYWW, put = WYWW)) TExtractType<4> agaa;
TExtractType<2> WZ() const { return ExtractComponent<2, 3, 2>(); } 
template <spv::StorageClass C1> void WZ(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 3, 2>(_var);}
void WZ(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZ, put = WZ)) TExtractType<2> wz;
__declspec(property(get = WZ, put = WZ)) TExtractType<2> ab;
TExtractType<3> WZX() const { return ExtractComponent<3, 3, 2, 0>(); } 
template <spv::StorageClass C1> void WZX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 0>(_var);}
void WZX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZX, put = WZX)) TExtractType<3> wzx;
__declspec(property(get = WZX, put = WZX)) TExtractType<3> abr;
TExtractType<4> WZXX() const { return ExtractComponent<3, 3, 2, 0, 0>(); } 
template <spv::StorageClass C1> void WZXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 0, 0>(_var);}
void WZXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZXX, put = WZXX)) TExtractType<4> wzxx;
__declspec(property(get = WZXX, put = WZXX)) TExtractType<4> abrr;
TExtractType<4> WZXY() const { return ExtractComponent<3, 3, 2, 0, 1>(); } 
template <spv::StorageClass C1> void WZXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 0, 1>(_var);}
void WZXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZXY, put = WZXY)) TExtractType<4> wzxy;
__declspec(property(get = WZXY, put = WZXY)) TExtractType<4> abrg;
TExtractType<4> WZXZ() const { return ExtractComponent<3, 3, 2, 0, 2>(); } 
template <spv::StorageClass C1> void WZXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 0, 2>(_var);}
void WZXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZXZ, put = WZXZ)) TExtractType<4> wzxz;
__declspec(property(get = WZXZ, put = WZXZ)) TExtractType<4> abrb;
TExtractType<4> WZXW() const { return ExtractComponent<3, 3, 2, 0, 3>(); } 
template <spv::StorageClass C1> void WZXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 0, 3>(_var);}
void WZXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZXW, put = WZXW)) TExtractType<4> wzxw;
__declspec(property(get = WZXW, put = WZXW)) TExtractType<4> abra;
TExtractType<3> WZY() const { return ExtractComponent<3, 3, 2, 1>(); } 
template <spv::StorageClass C1> void WZY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 1>(_var);}
void WZY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZY, put = WZY)) TExtractType<3> wzy;
__declspec(property(get = WZY, put = WZY)) TExtractType<3> abg;
TExtractType<4> WZYX() const { return ExtractComponent<3, 3, 2, 1, 0>(); } 
template <spv::StorageClass C1> void WZYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 1, 0>(_var);}
void WZYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZYX, put = WZYX)) TExtractType<4> wzyx;
__declspec(property(get = WZYX, put = WZYX)) TExtractType<4> abgr;
TExtractType<4> WZYY() const { return ExtractComponent<3, 3, 2, 1, 1>(); } 
template <spv::StorageClass C1> void WZYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 1, 1>(_var);}
void WZYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZYY, put = WZYY)) TExtractType<4> wzyy;
__declspec(property(get = WZYY, put = WZYY)) TExtractType<4> abgg;
TExtractType<4> WZYZ() const { return ExtractComponent<3, 3, 2, 1, 2>(); } 
template <spv::StorageClass C1> void WZYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 1, 2>(_var);}
void WZYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZYZ, put = WZYZ)) TExtractType<4> wzyz;
__declspec(property(get = WZYZ, put = WZYZ)) TExtractType<4> abgb;
TExtractType<4> WZYW() const { return ExtractComponent<3, 3, 2, 1, 3>(); } 
template <spv::StorageClass C1> void WZYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 1, 3>(_var);}
void WZYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZYW, put = WZYW)) TExtractType<4> wzyw;
__declspec(property(get = WZYW, put = WZYW)) TExtractType<4> abga;
TExtractType<3> WZZ() const { return ExtractComponent<3, 3, 2, 2>(); } 
template <spv::StorageClass C1> void WZZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 2>(_var);}
void WZZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZ, put = WZZ)) TExtractType<3> wzz;
__declspec(property(get = WZZ, put = WZZ)) TExtractType<3> abb;
TExtractType<4> WZZX() const { return ExtractComponent<3, 3, 2, 2, 0>(); } 
template <spv::StorageClass C1> void WZZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 2, 0>(_var);}
void WZZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZX, put = WZZX)) TExtractType<4> wzzx;
__declspec(property(get = WZZX, put = WZZX)) TExtractType<4> abbr;
TExtractType<4> WZZY() const { return ExtractComponent<3, 3, 2, 2, 1>(); } 
template <spv::StorageClass C1> void WZZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 2, 1>(_var);}
void WZZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZY, put = WZZY)) TExtractType<4> wzzy;
__declspec(property(get = WZZY, put = WZZY)) TExtractType<4> abbg;
TExtractType<4> WZZZ() const { return ExtractComponent<3, 3, 2, 2, 2>(); } 
template <spv::StorageClass C1> void WZZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 2, 2>(_var);}
void WZZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZZ, put = WZZZ)) TExtractType<4> wzzz;
__declspec(property(get = WZZZ, put = WZZZ)) TExtractType<4> abbb;
TExtractType<4> WZZW() const { return ExtractComponent<3, 3, 2, 2, 3>(); } 
template <spv::StorageClass C1> void WZZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 2, 3>(_var);}
void WZZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZZW, put = WZZW)) TExtractType<4> wzzw;
__declspec(property(get = WZZW, put = WZZW)) TExtractType<4> abba;
TExtractType<3> WZW() const { return ExtractComponent<3, 3, 2, 3>(); } 
template <spv::StorageClass C1> void WZW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 3>(_var);}
void WZW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZW, put = WZW)) TExtractType<3> wzw;
__declspec(property(get = WZW, put = WZW)) TExtractType<3> aba;
TExtractType<4> WZWX() const { return ExtractComponent<3, 3, 2, 3, 0>(); } 
template <spv::StorageClass C1> void WZWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 3, 0>(_var);}
void WZWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZWX, put = WZWX)) TExtractType<4> wzwx;
__declspec(property(get = WZWX, put = WZWX)) TExtractType<4> abar;
TExtractType<4> WZWY() const { return ExtractComponent<3, 3, 2, 3, 1>(); } 
template <spv::StorageClass C1> void WZWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 3, 1>(_var);}
void WZWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZWY, put = WZWY)) TExtractType<4> wzwy;
__declspec(property(get = WZWY, put = WZWY)) TExtractType<4> abag;
TExtractType<4> WZWZ() const { return ExtractComponent<3, 3, 2, 3, 2>(); } 
template <spv::StorageClass C1> void WZWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 3, 2>(_var);}
void WZWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZWZ, put = WZWZ)) TExtractType<4> wzwz;
__declspec(property(get = WZWZ, put = WZWZ)) TExtractType<4> abab;
TExtractType<4> WZWW() const { return ExtractComponent<3, 3, 2, 3, 3>(); } 
template <spv::StorageClass C1> void WZWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 2, 3, 3>(_var);}
void WZWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WZWW, put = WZWW)) TExtractType<4> wzww;
__declspec(property(get = WZWW, put = WZWW)) TExtractType<4> abaa;
TExtractType<2> WW() const { return ExtractComponent<2, 3, 3>(); } 
template <spv::StorageClass C1> void WW(const var_t<vec_type_t<base_type_t<T>, 2>, Assemble, C1>& _var) const { InsertComponent<2, 3, 3>(_var);}
void WW(const vec_type_t<base_type_t<T>, 2>& _var) const { InsertComponent<2, 3, 3>(var_t<vec_type_t<base_type_t<T>, 2>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WW, put = WW)) TExtractType<2> ww;
__declspec(property(get = WW, put = WW)) TExtractType<2> aa;
TExtractType<3> WWX() const { return ExtractComponent<3, 3, 3, 0>(); } 
template <spv::StorageClass C1> void WWX(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 0>(_var);}
void WWX(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWX, put = WWX)) TExtractType<3> wwx;
__declspec(property(get = WWX, put = WWX)) TExtractType<3> aar;
TExtractType<4> WWXX() const { return ExtractComponent<3, 3, 3, 0, 0>(); } 
template <spv::StorageClass C1> void WWXX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 0, 0>(_var);}
void WWXX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 0, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWXX, put = WWXX)) TExtractType<4> wwxx;
__declspec(property(get = WWXX, put = WWXX)) TExtractType<4> aarr;
TExtractType<4> WWXY() const { return ExtractComponent<3, 3, 3, 0, 1>(); } 
template <spv::StorageClass C1> void WWXY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 0, 1>(_var);}
void WWXY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 0, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWXY, put = WWXY)) TExtractType<4> wwxy;
__declspec(property(get = WWXY, put = WWXY)) TExtractType<4> aarg;
TExtractType<4> WWXZ() const { return ExtractComponent<3, 3, 3, 0, 2>(); } 
template <spv::StorageClass C1> void WWXZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 0, 2>(_var);}
void WWXZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 0, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWXZ, put = WWXZ)) TExtractType<4> wwxz;
__declspec(property(get = WWXZ, put = WWXZ)) TExtractType<4> aarb;
TExtractType<4> WWXW() const { return ExtractComponent<3, 3, 3, 0, 3>(); } 
template <spv::StorageClass C1> void WWXW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 0, 3>(_var);}
void WWXW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 0, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWXW, put = WWXW)) TExtractType<4> wwxw;
__declspec(property(get = WWXW, put = WWXW)) TExtractType<4> aara;
TExtractType<3> WWY() const { return ExtractComponent<3, 3, 3, 1>(); } 
template <spv::StorageClass C1> void WWY(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 1>(_var);}
void WWY(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWY, put = WWY)) TExtractType<3> wwy;
__declspec(property(get = WWY, put = WWY)) TExtractType<3> aag;
TExtractType<4> WWYX() const { return ExtractComponent<3, 3, 3, 1, 0>(); } 
template <spv::StorageClass C1> void WWYX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 1, 0>(_var);}
void WWYX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 1, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWYX, put = WWYX)) TExtractType<4> wwyx;
__declspec(property(get = WWYX, put = WWYX)) TExtractType<4> aagr;
TExtractType<4> WWYY() const { return ExtractComponent<3, 3, 3, 1, 1>(); } 
template <spv::StorageClass C1> void WWYY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 1, 1>(_var);}
void WWYY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 1, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWYY, put = WWYY)) TExtractType<4> wwyy;
__declspec(property(get = WWYY, put = WWYY)) TExtractType<4> aagg;
TExtractType<4> WWYZ() const { return ExtractComponent<3, 3, 3, 1, 2>(); } 
template <spv::StorageClass C1> void WWYZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 1, 2>(_var);}
void WWYZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 1, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWYZ, put = WWYZ)) TExtractType<4> wwyz;
__declspec(property(get = WWYZ, put = WWYZ)) TExtractType<4> aagb;
TExtractType<4> WWYW() const { return ExtractComponent<3, 3, 3, 1, 3>(); } 
template <spv::StorageClass C1> void WWYW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 1, 3>(_var);}
void WWYW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 1, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWYW, put = WWYW)) TExtractType<4> wwyw;
__declspec(property(get = WWYW, put = WWYW)) TExtractType<4> aaga;
TExtractType<3> WWZ() const { return ExtractComponent<3, 3, 3, 2>(); } 
template <spv::StorageClass C1> void WWZ(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 2>(_var);}
void WWZ(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZ, put = WWZ)) TExtractType<3> wwz;
__declspec(property(get = WWZ, put = WWZ)) TExtractType<3> aab;
TExtractType<4> WWZX() const { return ExtractComponent<3, 3, 3, 2, 0>(); } 
template <spv::StorageClass C1> void WWZX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 2, 0>(_var);}
void WWZX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 2, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZX, put = WWZX)) TExtractType<4> wwzx;
__declspec(property(get = WWZX, put = WWZX)) TExtractType<4> aabr;
TExtractType<4> WWZY() const { return ExtractComponent<3, 3, 3, 2, 1>(); } 
template <spv::StorageClass C1> void WWZY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 2, 1>(_var);}
void WWZY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 2, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZY, put = WWZY)) TExtractType<4> wwzy;
__declspec(property(get = WWZY, put = WWZY)) TExtractType<4> aabg;
TExtractType<4> WWZZ() const { return ExtractComponent<3, 3, 3, 2, 2>(); } 
template <spv::StorageClass C1> void WWZZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 2, 2>(_var);}
void WWZZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 2, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZZ, put = WWZZ)) TExtractType<4> wwzz;
__declspec(property(get = WWZZ, put = WWZZ)) TExtractType<4> aabb;
TExtractType<4> WWZW() const { return ExtractComponent<3, 3, 3, 2, 3>(); } 
template <spv::StorageClass C1> void WWZW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 2, 3>(_var);}
void WWZW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 2, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWZW, put = WWZW)) TExtractType<4> wwzw;
__declspec(property(get = WWZW, put = WWZW)) TExtractType<4> aaba;
TExtractType<3> WWW() const { return ExtractComponent<3, 3, 3, 3>(); } 
template <spv::StorageClass C1> void WWW(const var_t<vec_type_t<base_type_t<T>, 3>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 3>(_var);}
void WWW(const vec_type_t<base_type_t<T>, 3>& _var) const { InsertComponent<3, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 3>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWW, put = WWW)) TExtractType<3> www;
__declspec(property(get = WWW, put = WWW)) TExtractType<3> aaa;
TExtractType<4> WWWX() const { return ExtractComponent<3, 3, 3, 3, 0>(); } 
template <spv::StorageClass C1> void WWWX(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 3, 0>(_var);}
void WWWX(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 3, 0>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWWX, put = WWWX)) TExtractType<4> wwwx;
__declspec(property(get = WWWX, put = WWWX)) TExtractType<4> aaar;
TExtractType<4> WWWY() const { return ExtractComponent<3, 3, 3, 3, 1>(); } 
template <spv::StorageClass C1> void WWWY(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 3, 1>(_var);}
void WWWY(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 3, 1>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWWY, put = WWWY)) TExtractType<4> wwwy;
__declspec(property(get = WWWY, put = WWWY)) TExtractType<4> aaag;
TExtractType<4> WWWZ() const { return ExtractComponent<3, 3, 3, 3, 2>(); } 
template <spv::StorageClass C1> void WWWZ(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 3, 2>(_var);}
void WWWZ(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 3, 2>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWWZ, put = WWWZ)) TExtractType<4> wwwz;
__declspec(property(get = WWWZ, put = WWWZ)) TExtractType<4> aaab;
TExtractType<4> WWWW() const { return ExtractComponent<3, 3, 3, 3, 3>(); } 
template <spv::StorageClass C1> void WWWW(const var_t<vec_type_t<base_type_t<T>, 4>, Assemble, C1>& _var) const { InsertComponent<3, 3, 3, 3, 3>(_var);}
void WWWW(const vec_type_t<base_type_t<T>, 4>& _var) const { InsertComponent<3, 3, 3, 3, 3>(var_t<vec_type_t<base_type_t<T>, 4>, Assemble, spv::StorageClassFunction>(_var));}
__declspec(property(get = WWWW, put = WWWW)) TExtractType<4> wwww;
__declspec(property(get = WWWW, put = WWWW)) TExtractType<4> aaaa;
#endif // !SPEAR_SPIRVVECTORCOMPONENTACCESS_H
