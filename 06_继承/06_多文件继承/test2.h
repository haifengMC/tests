#pragma once

class B : public A, public tA<B>
{
public:
	int b = 20;
	B() : tA(this) {}

};
