#pragma once

#ifndef NETCONV
#define NETCONV

#define TYP_INIT 0
#define TYP_SMLE 1
#define TYP_BIGE 2

unsigned long long htonll(unsigned long long src);
unsigned long long ntohll(unsigned long long src);

#endif
