main()
{
	_AH=1;
	_AH=_AH<<1;
	*(char far *)0xb8000001&=0xf8;
	*(char far *)0xb8000001|=_AH;
	*(char far *)0xb8000000='a';
}