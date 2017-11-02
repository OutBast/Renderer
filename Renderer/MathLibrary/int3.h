#pragma once
class int3
{
public:
	int3();
	int3(int value);
	int3(int x, int y, int z);
	~int3();
	
#pragma region Overloaded Operators
	int& operator[] (size_t n) { return v[n]; }
	const int& operator[] (size_t n) const { return v[n]; }
#pragma endregion Overloaded Operators

private:
	union
	{
		struct  
		{
			int x, y, z;
		};

		int v[3];
	};
};

