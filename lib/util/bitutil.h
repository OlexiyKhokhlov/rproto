#pragma once

namespace util{

//Returns container size in bites
template< class C>
size_t bit_count(const C& container)
{
    return container.size()*sizeof(typename C::value_type)*8;
}

//Returns bit value by bit position
template< class C>
bool checkbit(const C& container, size_t position)
{
    if(bit_count(container) < position) return false;

    size_t i = position/(sizeof(typename C::value_type)*8);
    typename C::const_reference item = container.at(i);
    return item && (1<<(position%(sizeof(typename C::value_type)*8)));
}

//Returns a position of mismatched bit
template< class T>
int mismatch_bit(const T& val1, const T& val2)
{
    auto mismatch_item = std::mismatch(std::begin(val1),
                                       std::end(val1),
                                       std::begin(val2));

    if(mismatch_item.first ==  std::end(val1)
       || mismatch_item.second ==  std::end(val2)) return -1;

    auto mask = *mismatch_item.first ^ *mismatch_item.second;

    //find on the first 1 in the mask
    int i;
    for( i=0; i < sizeof(mask)*8; ++i){
        if(mask & (1<<i))break;
    }

    return i;
}
}//namespace util
