#include "SingleLattice.h"

void SingleLattice::completeFlip(const int& step, const double& temperature)
{
	for (auto step_index = 0; step_index != step; ++step_index)
	{
		lattice.flipOnePoint(temperature);

		//Output data for "each" flip:
		//TODO: This is for test only.
		if ((step_index + 1) % (step / $DATA_NUMBER) == 0)
		{
			auto stepNumber = (step_index + 1) / (step / $DATA_NUMBER) - 1;
			auto iter = flipData.begin() + stepNumber;
			*iter = lattice.physicalQuantity;
		}

		//For "the last 10" steps:
		for (auto i = 0; i != 10; ++i)
			if (step_index == (step / (10 * $LAST_10_PERCENT)) * (10 * ($LAST_10_PERCENT - 1) + i))
				//Now "result" is the total value.
				result += lattice.physicalQuantity;
	}
}
