#pragma once

#define SAFE_DELETE(x)          if(x!=nullptr)delete x;
#define SAFE_DELETE_MULTI(x)    if(x!=nullptr)delete[] x;