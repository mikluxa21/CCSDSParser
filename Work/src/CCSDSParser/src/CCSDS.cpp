#include <CCSDS.h>


//template <class TypeCCSDS> CCSDS<TypeCCSDS>::CCSDS(TypeCCSDS& packageCCSDS, size_t packageLen, size_t packageChanged)


template<class TypeCCSDS>
size_t CCSDS<TypeCCSDS>::getCountUsedByte() { return this->countUsedByte;}


