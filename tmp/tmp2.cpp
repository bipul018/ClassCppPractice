
int main1();

int main2();

#include <cmath>
#include <iostream>
#include <random>

int main2() {


	constexpr unsigned C_in = 2;
	constexpr unsigned C_out = 2;
	constexpr unsigned C_b = 2;

	float ws[C_in][C_out] = { {0,0},{0,0} };
	float bs[C_out] = { 0,0 };
	float ins[C_in] = { 0,0 };
	float outs[C_out] = { 0,0 };
	float touts[C_out] = { 0,0 };

	auto evaluateOuts = [&]() {

		if (ins[0] <= ins[1]) {
			outs[0] = 1;
			outs[1] = 0;
		}
		else {
			outs[0] = 0;
			outs[1] = 1;
		}

	};

	auto getOutput = [&]() {
		for (int i = 0; i < C_out; ++i) {
			touts[i] = 0;
			for (int j = 0; j < C_in; ++j) {
				touts[i] += ws[j][i] * ins[j];
			}
			touts[i] += bs[i];
		}
	};

	auto getError = [&](int n) {
		return touts[n] - outs[n];
	};

	auto getDeri = [&](int o, int w) {

		return ins[w];

	};
	auto getCost = [&](int o) {
		return getError(o) * getError(o);
	};



	using namespace std;

	auto getSign = [](float x) {
		if (x > FLT_EPSILON * 10.f)
			return 1.f;
		else if (x < FLT_EPSILON * 10.f)
			return -1.f;
		else
			return 0.f;
	};

	float currCost = 0;
	for (float x = -10; x <= 10; x += 0.1f) {

		currCost += getCost(x) * getCost(x);
	}
	char c = getchar();

	mt19937_64 rng(random_device{}());
	uniform_int_distribution<int> dist{ 0,10 };

	while (c != 'n') {
		c = 'v';
		c = getchar();

		float step = 0.002;
		//float sums[2] = { 0,0 };

		static float sums[C_in][C_out]{ 0 };
		static float bsums[C_out]{ 0 };

		double sumCost = 0.f;
		int costcount = 0;

		for (auto& i : ins) {
			i = dist(rng);
		}
		evaluateOuts();
		getOutput();

		for (int i = 0; i < C_out; ++i) {
			for (int j = 0; j < C_in; ++j) {

				sums[j][i] += getError(i) * 2.f * getDeri(i, j);

			}
			bsums[i] += getError(i) * 2.f;
			sumCost += getCost(i);
			costcount++;
		}

		//for (float x = 0.5; x <= 10; x += 0.1f) {
		//
		//	for (int i = 0; i < 2; ++i) {
		//		sums[i] += getError(x) * 2.f * getDerivative(x, i);
		//		//sums[i] += getDerivative(x, i) * getSign(getError(x));
		//	}
		//
		//}

		//for (int i = 0; i < 2; ++i) {
		//	as[i] -= step * sums[i];
		//}

		if (c == 'a') {


			for (int i = 0; i < C_out; ++i) {
				for (int j = 0; j < C_in; ++j) {

					ws[j][i] -= step * sums[j][i];

				}
				bs[i] -= step * bsums[i];

			}
			for (auto& s : sums) {
				for (auto& ss : s) {
					ss = 0;
				}
			}
			for (auto& bs : bsums)
				bs = 0;
		}
		cout << "in\t";
		for (auto& i : ins)
			cout << i << "\t";
		cout << "out\t";
		for (auto& o : outs)
			cout << o << "\t";
		cout << "tout\t";
		for (auto& to : touts)
			cout << to << "\t";


		cout << sumCost / costcount << endl;

	}





	return 0;
}


int main(int argc, const char* argv[]) {
	main1();
}