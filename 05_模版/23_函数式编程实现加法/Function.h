#ifndef _MY_FUNCTION_H_
#define _MY_FUNCTION_H_

#include <string>
#include <functional>
#include <xutility>

template<typename Container>
using ValTy = typename std::_Get_first_parameter<Container>::type;
template<typename Container>
ValTy<Container>& forEach(
	std::function<void(ValTy<Container>&, const ValTy<Container>&)> f, 
	ValTy<Container>& out, const Container& in)
{
	for(auto& x : in)
		f(out, x);

	return out;
}

template<typename T, typename Container>
T& sum(T& out, const Container& in)
{
	return forEach<Container>(
		[](ValTy<Container>& x, const ValTy<Container>& y) {
			x += y;
		}, static_cast<ValTy<Container>&>(out), in);
}


template<typename Container>
std::string& concat(std::string& out, const Container& in)
{
	return forEach<Container>(
		[](std::string& x, const std::string& y) {
			x.append(y);
		}, out, in);
}



#endif
