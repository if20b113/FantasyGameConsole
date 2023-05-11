
	class Vec2D : Vec
	{
	private:
		// Intentionally not using m_
		int x;
		int y;
	public:
		Vec2D();
		void AdjustVector(int const Addx, int const Addy);
		void SetVector(int const x, int const y);
	};

	class Vec // Interface
	{
	public:
		virtual ~Vec(){};
		virtual void AdjustVector(int const Addx, int const Addy) = 0;
		virtual void SetVector(int const x, int const y) = 0;
	};