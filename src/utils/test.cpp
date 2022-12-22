#include <cstdlib>
#include "test.h"

int QwikMath::divide(int a, int b)
{
	int ans = 0;

	bool neg = a < 0 || b < 0;

	unsigned int ua = abs(a);
	unsigned int ub = abs(b);

	for (int i = 31; i >= 0; i--)
	{
		if (ub << i <= ua) {
			ua -= ub << i;
			ans += 1 << i;
		}
	}

	return neg ? -ans : ans;
}
