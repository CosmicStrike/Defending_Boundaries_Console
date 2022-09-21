#pragma once

#if defined UNICODE

typedef wchar_t M_CHARS;

#else
typedef char M_CHARS;

#endif // UNICODE


#ifndef math
#include<math.h>
#endif

//++++++++++++                GAME_ENGINE_STUFF              +++++++++++++++++++


//0 -> Positions Structure For All Characters
struct Position
{
	//this Position in int to display in array
	int iX;
	int iY;

	//this Position in float to Calculate Next Position per sec
	float fX;
	float fY;


	Position() :iX(0), iY(0), fX(0.0f), fY(0.0f)
	{}

	Position(int X, int Y) :iX(X), iY(Y), fX(X), fY(Y)
	{}


	void operator*=(const float& Value) 
	{ this->fX *= Value;
	    this->fY *= Value;
	    this->iY *= Value;
	    this->iY *= Value;
	}

	void operator/=(const float& Value)
	{
		this->fX/= Value;
		this->fY /= Value;
		this->iY /= Value;
		this->iY /= Value;
	}

};


//1->       -------------------------------  Vector2D  -------------------------------------

//Conversion Factor
const float RadiansToDegrees = 180.0f / 3.1415f;
const float DegreesToRadians = 3.1415f / 180.0f;

struct Vector2D
{
	//Calculated Values of vector along x-axis and y-axis
	float X;
	float Y;
	
protected:

	//these from and to coordinates to choose new origin
	float From_X;
	float From_Y;

	float To_X;
	float To_Y;


	//Mag=Magnitude and angle made by vector w.r.t horizontal axis i.e positive x-axis
	float Mag;
	float DirectionAngle;


	//bool value to avoid double conversion 
	bool IsInDegree = false;


public:


	//default constructor
	Vector2D()
	{
		From_X = 0;
		From_Y = 0;
		To_X = 0;
		To_Y = 0;
		X = 0;
		Y = 0;
		Mag = 0.0f;
		DirectionAngle = 0.0f;

		IsInDegree = false;
	}


	//consyructor of vector in which origin is at (0,0)
	Vector2D(float x, float y) :X(x), Y(y)
	{
		From_X = 0.0f;
		From_Y = 0.0f;
		To_X = 0;
		To_Y = 0;


		Mag = sqrtf((X * X) + (Y * Y));


		//it only adjust the angle between the range 0 to 360
		DirectionAngle = atan2f(Y, X);    //Converts to Radian
		if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);


		IsInDegree = false;


	}


	//constructor of vector in which origin if (From_X ,From_Y) and (To_X,To_Y) is destination
	Vector2D(float From_x, float From_y, float To_x, float To_y)
	{
		if ((To_x == From_x) && (To_y == From_y))
		{
			From_X = 0;
			From_Y = 0;
			To_X = 0;
			To_Y = 0;
			X = 0;
			Y = 0;
			Mag = 0.0f;
			DirectionAngle = 0.0f;

			IsInDegree = false;
		}
		else
		{
			To_X = To_x;
			To_Y = To_y;
			From_X = From_x;
			From_Y = From_y;
			IsInDegree = false;
			X = To_X - From_X;
			Y = To_Y - From_Y;

			Mag = sqrtf(((X) * (X)) + ((Y) * (Y)));

			//it only adjust the angle between the range 0 to 360
			DirectionAngle = atan2f(Y, X);               //Converts to Radian
			if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);
		}
	}



	//Section-1
	//contains all operators overloaded for vector arithmatic

	Vector2D operator +(const Vector2D& RHS) const    { return  Vector2D(X + RHS.X, Y + RHS.Y); }
	Vector2D operator -(const Vector2D& RHS)const       { return  Vector2D(X - RHS.X, Y - RHS.Y); }
	Vector2D operator/(const float& Value)const              { return  Vector2D(X / Value, Y / Value); }
	Vector2D operator*(const float& Value)const              { return  Vector2D(X * Value, Y * Value); }
	void operator+=(const Vector2D& RHS); 
	void  operator-=(const Vector2D& RHS);
	void operator/=(const float& Value);
	void operator*=(const float& Value);
	void operator =(const Vector2D& RHS);

	bool operator!=(const Vector2D& RHS) const               { return ((X != RHS.X) && (Y != RHS.Y) && (DirectionAngle != RHS.DirectionAngle)); }
	bool operator==(const Vector2D& RHS) const              { return ((X == RHS.X) && (Y == RHS.Y) && (DirectionAngle == RHS.DirectionAngle)); }


	//Section-2
	//contains  functions for user help

	//Magnitude becomes 1 we get unit vector pointing in that direction
	void Normalize();
	float GetMagnitude() { return Mag; }
	float GetDirection() { return DirectionAngle; }

	void RadiansTo_Degree();          //Changes Angle From Rad To Deg
	void DegreesTo_Radians();       //Changes Angle From Deg To Rad



	//Section-3
	//contains manipluation of vector coordinates and angle by user
	void Subtract_InEach(const float& Value);
	void Add_InEach(const float& Value);

	void AngleChange_InDegrees(const float& Angle_InDegree);      //Make angle change in degrees( inputs in Degrees)
	void AngleChange_InRadians(const float& Angle_InRadian);      //Make angle change in radians (inputs in radians)



	//Section-4
	//contains vector sclar product formule
	float SclarProduct(const Vector2D& RHS)const { return ((X * RHS.X) + (Y * RHS.Y)); }
	Vector2D ParallelogramAddition(const Vector2D&);



	//Destructor
	~Vector2D() {}

};


//2 >  --------------------------------- Vectors Template (Generic Vector) -----------------------
template<typename T>
struct Generic_Vector
{
	T X;
	T Y;



	Generic_Vector() :X(0), Y(0)
	{}

	Generic_Vector(T x, T y) :X(x), Y(y)
	{}



	Generic_Vector<T> operator +(const Generic_Vector<T>& RHS) { return Generic_Vector<T>(X + RHS.X, Y + RHS.Y); }
	Generic_Vector<T> operator -(const Generic_Vector<T>& RHS) { return Generic_Vector<T>(X - RHS.X, Y - RHS.Y); }
	Generic_Vector<T> operator /(const T& Value) { return Generic_Vector<T>(X / Value, Y / Value); }
	Generic_Vector<T> operator*(const T& Value) { return Generic_Vector<T>(X * Value, Y * Value); }

	void operator+=(const Generic_Vector<T>& RHS) { this->X += RHS.X;this->Y += RHS.Y; }
	void operator-=(const Generic_Vector<T>& RHS) { this->X -= RHS.X;this->Y -= RHS.Y; }
	void operator/=(const T& Value) { this->X /= Value;this->Y /= Value; }
	void operator*=(const T& Value) { this->X *= Value;this->Y *= Value; }


	bool operator==(const Generic_Vector<T>& RHS) { return (X == RHS.X && Y == RHS.Y); }
	bool operator!=(const Generic_Vector<T>& RHS) { return (X != RHS.X && Y != RHS.Y); }


	T SclarProduct(const Generic_Vector<T>& RHS) { return (X * RHS.X + Y * RHS.Y); }
	T Mag() { return (T)sqrtf((this->X * this->X) + (this->Y * this->Y)); }
	void Normalize()
	{
		T Magitude = this->Mag();
		this->X /= Magitude;
		this->Y /= Magitude;
	}
};


//3 >  -----------------------            KEYS Structure     -------------------------------------
struct RotationalMec
{
	float Magnitude;
	enum Rotation { ClockWise, AntiClockWise };
	bool Direction;


	RotationalMec()
	{
		Magnitude = 0.0f;
		Direction = ClockWise;
	}
};


//4 >  -----------------------            KEYS Structure     -------------------------------------

struct M_Keys
{
	bool KeyPressed;
	bool KeyHold;

	M_Keys()
	{
		KeyPressed = false;
		KeyHold = false;
	}
};


//5 >  -----------------------             GAME UTILITIES FUNCTIONS     -------------------------------------


bool DrawLine(M_CHARS* Screen,const  Generic_Vector<int>& Screen_Resolution,const Position& From ,const Position& To,const M_CHARS& Line_Symbol)
{
	Vector2D LineDirection(From.iX, From.iY, To.iX, To.iY);

	Position CurrPosition(From.iX, From.iY);
	
	float x = 0.0f, y = 0.0f;

	float LineMag = 0.0f;
	//LineDirection.Normalize();
	LineDirection.DegreesTo_Radians();

	//if (From.iX > To.iX || From.iY > To.iY)return false;
	
	while (LineMag<=LineDirection.GetMagnitude())
	{
		if (CurrPosition.iX == To.iX && CurrPosition.iY == To.iY)break;

		x = CurrPosition.fX;
		y = CurrPosition.fY;

		Screen[CurrPosition.iY * Screen_Resolution.X + CurrPosition.iX] = Line_Symbol;

		CurrPosition.fX += cosf(LineDirection.GetDirection());
		CurrPosition.fY += sinf(LineDirection.GetDirection());
		
		LineMag += sqrtf(((CurrPosition.fX - x) * (CurrPosition.fX - x)) + ((CurrPosition.fY - y) * (CurrPosition.fY - y)));

		CurrPosition.iX = CurrPosition.fX;
		CurrPosition.iY = CurrPosition.fY;

	}
	return true;
}

bool DrawRectangle(M_CHARS* Screen, const  Generic_Vector<int>& Screen_Resolution, const Position& LeftX_TopY_Coord, const Position& RightX_BottomY_Coord, const M_CHARS& Rectangle_OutLine_Symbol)
{
	if (RightX_BottomY_Coord.iX < LeftX_TopY_Coord.iX || RightX_BottomY_Coord.iY < LeftX_TopY_Coord.iY)
		return false;
	else if (LeftX_TopY_Coord.iX<=0 || LeftX_TopY_Coord.iY <= 0 || RightX_BottomY_Coord.iX >= Screen_Resolution.X || RightX_BottomY_Coord.iY >= Screen_Resolution.Y)
	{
		return false;
	}
	else
	{
		int RectHeight = RightX_BottomY_Coord.iY - LeftX_TopY_Coord.iY;
		int RectWidth = RightX_BottomY_Coord.iX - LeftX_TopY_Coord.iX;

		if (RectHeight <= 0 || RectWidth <= 0) return false;
		else
		{			
				//Left Vertical Line
				DrawLine(Screen, Screen_Resolution, LeftX_TopY_Coord, { LeftX_TopY_Coord.iX,LeftX_TopY_Coord.iY + RectHeight }, Rectangle_OutLine_Symbol);
				
				//Top Horizontal Line
				DrawLine(Screen, Screen_Resolution, LeftX_TopY_Coord, { LeftX_TopY_Coord.iX+RectWidth,LeftX_TopY_Coord.iY}, Rectangle_OutLine_Symbol);
			
				//Right Vertical Line
				DrawLine(Screen, Screen_Resolution, { LeftX_TopY_Coord.iX + RectWidth,LeftX_TopY_Coord.iY },RightX_BottomY_Coord, Rectangle_OutLine_Symbol);
				
				//Bottom Horizonatal Line
				DrawLine(Screen, Screen_Resolution, { LeftX_TopY_Coord.iX,LeftX_TopY_Coord.iY + RectHeight }, { RightX_BottomY_Coord.iX+1, RightX_BottomY_Coord.iY }, Rectangle_OutLine_Symbol);
			

		}

	}

	return true;
}

bool FillRectangle(M_CHARS* Screen, const  Generic_Vector<int>& Screen_Resolution, const Position& LeftX_TopY_Coord, const Position& RightX_BottomY_Coord, const M_CHARS& Rectangle_OutLine_Symbol,const M_CHARS& Filling_Symbol)
{

	if (DrawRectangle(Screen, Screen_Resolution, LeftX_TopY_Coord, RightX_BottomY_Coord, Rectangle_OutLine_Symbol))
	{
		int RectHeight = RightX_BottomY_Coord.iY - LeftX_TopY_Coord.iY;
		int RectWidth = RightX_BottomY_Coord.iX - LeftX_TopY_Coord.iX;

		RectHeight -= 1;
		RectWidth -= 1;

		Position CurrPos(LeftX_TopY_Coord.iX+1, LeftX_TopY_Coord.iY+1);

		for(int x=0;x<RectWidth;x++)
			for (int y = 0;y < RectHeight;y++)
			{
				Screen[(CurrPos.iX + x) + (CurrPos.iY + y) * Screen_Resolution.X] = Filling_Symbol;
			}

	}
	else
	{
		return false;
	}



	return true;
}

bool DrawCircle(M_CHARS* Screen, const  Generic_Vector<int>& Screen_Resolution, const Position& Center, float  Radius, int Offset = 0)
{
	Position DrawingPos;

	//Check if randomness varible is greater than Radius
	if (Offset >= Radius)return false;


	//Checks Radius if it is less than 0,0 and greater than feild
	if (Center.iX <= 0 || Center.iY <= 0 || Center.iX >= Screen_Resolution.X - Radius || Center.iY >= Screen_Resolution.Y - Radius)return false;

	for (int i = 0;i <= 360;i += 1)
	{
			
		DrawingPos.fX = (Radius * cosf(i * DegreesToRadians)) + Center.iX;
		DrawingPos.fY = (Radius * sinf(i * DegreesToRadians)) + Center.iY;

		DrawingPos.iX = DrawingPos.fX;
		DrawingPos.iY = DrawingPos.fY;

		Screen[DrawingPos.iX + DrawingPos.iY * Screen_Resolution.X] = L'O';
	}


}


//+++++++++++COMMON INTERFACE BETWEEN PHYSICS AND MATH+++++++++++

//INTERFACE OF PHYSICS

namespace Physic
{
	enum eCharge { Positive, Negative };

	// 0-->    ----------------- --             Class ------  Time            ----------------------------------

	class Time
	{
		int iHours;
		int iMinutes;
		int iSeconds;
		float fSeconds;


		int TimeToNumber();            //Returns Number which is calculated from time i.e smallest unit time seconds
		void NumberToTime(const int Number);           //converts given number to time i.e seconds and minutes , hours

	public:

		Time()
		{
			iHours = 0;
			iMinutes = 0;
			iSeconds = 0;
			fSeconds = 0.0f;
		}

		Time(int hours, int minutes, int seconds)
		{
			if (hours >= 0 && minutes >= 0 && seconds >= 0)
			{
				int Total = (hours * 60 * 60) + (minutes * 60) + seconds;
				int min, hor;

				int sec = Total % 60;
				int min_t = Total / 60;

				if (min_t > 59)
				{
					min = min_t % 60;
					hor = min_t / 60;
				}
				else
				{
					min = min_t;
					hor = 0;
				}
			
				iHours = hor;
				iMinutes = min;
				iSeconds = sec;
				fSeconds = iHours * 60 * 60 + iMinutes * 60 + iSeconds;
			}
		}

	public:

		//operator functions
		bool operator ==(const Time& RHS)               { return ((iHours == RHS.iHours) && (iMinutes == RHS.iMinutes) && (iSeconds == RHS.iSeconds));    }
		bool operator !=(const Time& RHS)                 { return ((iHours != RHS.iHours) && (iMinutes != RHS.iMinutes) && (iSeconds != RHS.iSeconds));         }
		void operator =(const Time& RHS)                   { iHours = RHS.iHours; iMinutes = RHS.iMinutes; iSeconds = RHS.iSeconds; fSeconds = RHS.fSeconds;  }

		void operator +=(Time& RHS);
		void operator -=(Time& RHS);
		void operator *=(const int& Value);
		void operator /=(const int& Value);

		Time operator +(Time& RHS);
		Time operator -(Time& RHS);
		Time operator *(const int& Value);
		Time operator /(const int& Value);

		//Arithmatic Functions
		void AddIn_Seconds(const int& Value);
		void AddIn_Minutes(const int& Value);
		void AddIn_Hours(const int& Value);

		void SubtractFrom_Seconds(const int& Value);
		void SubtractFrom_Minutes(const int& Value);
		void SubtractFrom_Hours(const int& Value);

		void AddIn_FSeconds(const float& Value);
		void SubtractFrom_FSeconds(const float& Value);

		//Return Values
		int Get_Seconds()                                            { return iSeconds;}
		int Get_Minutes()                                            { return iMinutes;}
		int Get_Hours()                                               { return iHours;   }
		float Get_FSeconds()                                       { return fSeconds; }
		bool IsTimeOver()                                           { return !(iHours * 60 * 60 + iMinutes * 60 + iSeconds); }
	};


	class Particles
	{
	protected:

		Vector2D Velocity;
		Vector2D Accleration;


	public:

		float Mass;
		Position ParPos;


	public:

		Particles()
		{
			Mass = 0.0f;
			ParPos *= 0.0f;

		}

		Particles(float mass, Position ParticlePos) :Mass(mass), ParPos(ParticlePos)
		{

		}

		//Mass Independent         v v v  v v v  v v v  v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v 


		//Sets Acceralation to specific value
		void SetAccleration(float Magnitude, const Vector2D& Direction);

		//Acclerate by constant acc whose magnitude is store in Accleration
		void Acclerate(const float& fElapsedTime);

		//in Each all Increases accleartion and updates the position
		void Move_With_IncreasingAcc(const float& fElapsedTime);

		//Sets Velocity to specific value
		void Set_Velocity(float Magnitude, const  Vector2D& Direction);

		//All these above Functions Are Mass InDependent  ^^^^^^^^^^^^^^^^^^^^^


		//Recalucates the position by adding velocity
		void  Update_Position(const float& fElapsedTime);

		float GetAccleration() { return Accleration.GetMagnitude(); }

		float GetVelocity() { return Velocity.GetMagnitude(); }



		//operator overloading
		void operator =(const Particles& RHS)
		{
			Velocity = RHS.Velocity;
			Accleration = RHS.Accleration;
			Mass = RHS.Mass;
			ParPos = RHS.ParPos;
		}


		//Virtual Function So that This Particle Class is not define
		virtual void Not_TO_Define() = 0;

		~Particles()
		{}

	};


	class Neutral_Particles :public Particles
	{
		float KineticEnergy;
		float PotentialEnergy;
		Vector2D Momentum;
		float Height;

	public:

		Neutral_Particles() :Particles(0.0f, { 0,0 })
		{
			KineticEnergy = 0.0f;
			PotentialEnergy = 0.0f;
			Height = 0.0f;
		}

		Neutral_Particles(float mass, Position PositionParticle, const Position& Bottom_Ground) :Particles(mass, PositionParticle)
		{
			Height = Bottom_Ground.iY - ParPos.iY;
			KineticEnergy = 1 / 2 * Mass * Velocity.GetMagnitude() * Velocity.GetMagnitude();
			PotentialEnergy = Mass * Height * 9.81f;

			//Momentum HAs Direction of Velocity   == ->>  Momentum = Mass * Velocity
			Momentum = Velocity;
			Momentum.Normalize();
			Momentum *= Mass * Velocity.GetMagnitude();

		}

		float Get_KineticEnergy() { return 1 / 2 * Mass * Velocity.GetMagnitude() * Velocity.GetMagnitude(); }

		float Get_PotentialEnergy() { return Mass * Height * 9.81f; }

		float Get_Momentum_Mag() { return Momentum.GetMagnitude(); }

		float Get_Height() { return Height; }


		void Update_ParticlePhysic(const Position& Bottom_Ground);


		void operator = (const Neutral_Particles& RHS)
		{
			Velocity = RHS.Velocity;
			Accleration = RHS.Accleration;
			Mass = RHS.Mass;
			ParPos = RHS.ParPos;
			KineticEnergy = RHS.KineticEnergy;
			PotentialEnergy = RHS.PotentialEnergy;
			Height = RHS.Height;
			Momentum = RHS.Momentum;
		}


		//Virtual Function from class Particles
		void Not_TO_Define() {};

	};


	class Charge_Particles :public Particles
	{
		int Charge;
		float KineticEnergy;
		float PotentialEnergy;
		float Momentum;
		float ChargePotential;
		float MagnitudeOfCharge;


	public:

		Charge_Particles() :Particles(0, { 0,0 })
		{
			Charge = Positive;
			MagnitudeOfCharge = 0.0f;
		}

		Charge_Particles(float mass, Position ParticlePos, float Magnitudeof_charge, eCharge charge) :Particles(mass, ParticlePos), MagnitudeOfCharge(Magnitudeof_charge), Charge(charge)
		{}


	};


	class RigidBody :public Particles
	{
	protected:
		RotationalMec Angular_Displacement;
		RotationalMec Angular_Veloctiy;
		RotationalMec Angular_Accleration;


	public:

		RigidBody()
		{}


	public:



		void virtual Not_TO_Define() = 0;

		~RigidBody()
		{}

	};


	class Plane2D :public RigidBody
	{
	public:

		enum OriginPoint { Center, BottomLeft };

	private:
		int iHeight;
		int iWidth;
		bool PovitPointSet;
		OriginPoint PovitPoint;
		float PreviousAngularDisplacement_ToDraw;



	public:

		Plane2D()
		{
			iHeight = 0.0f;
			iWidth = 0.0f;
			PovitPointSet = false;
			Mass = 0.0f;
		
			PreviousAngularDisplacement_ToDraw=0.0f;
		}

		Plane2D(float mass, OriginPoint OriginPivotPoint, Position OriginCoord, int width, int height)
		{
			if (mass > 0.000001f)
				Mass = mass;
			else
				Mass = 0.00000f;

			if (height > 0 && width > 0)
			{
				iHeight = height;
				iWidth = width;
			}

			
			PreviousAngularDisplacement_ToDraw = 0.0f;

			if (OriginCoord.iX > 0 && OriginCoord.iY > 0)
			{
				ParPos = OriginCoord;
			}

			switch (OriginPivotPoint)
			{
			case Center:
			{
				PovitPoint = Center;
				PovitPointSet = true;
				
				break;
			}
			case BottomLeft:
			{
				PovitPoint = BottomLeft;
				PovitPointSet = true;
			
				break;
			}
			default:
			{
				PovitPoint = Center;
				PovitPointSet = true;
				break;
			}
			}
		}
	
	

	public:

		void Draw(M_CHARS* Screen, const  Generic_Vector<int>& Screen_Resolution,const M_CHARS& PLaneSymbol);

		void Set_AngularDisplacement_InRad(const float& Value,bool AntiClockWise);
		void Set_AngularVelocity_InRad(const float& Value, bool AntiClockWise);
		void Set_AngularAccleration_InRad(const float& Value, bool AntiClockWise);

		void Update_Rotation(const float& fElaspedTime);

		void  Not_TO_Define() {};
		~Plane2D()
		{}

	};


}









//======================================================





namespace Direction
{
	Vector2D v2dUp(0, -1);
	Vector2D v2dDown(0, 1);
	Vector2D v2dLeft(-1, 0);
	Vector2D v2dRight(1, 0);
}





































































//GAME STUFF IMPLEMENTATION

//1->       -------------------------------  Vector2D  -------------------------------------


//Section-1  implementation in Interface 

void Vector2D::operator+=(const Vector2D& RHS)
{
	this->X += RHS.X;
	this->Y += RHS.Y;

	this->Mag = sqrtf(X * X + Y * Y);

	this->DirectionAngle = atan2f(Y, X);
	if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);

}


void Vector2D::operator-=(const Vector2D& RHS)
{
	this->X -= RHS.X;
	this->Y -= RHS.Y;

	this->Mag = sqrtf(X * X + Y * Y);

	this->DirectionAngle = atan2f(Y, X);
	if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);
}


void Vector2D::operator*=(const float& Value)
{
	this->X *= Value;
	this->Y *= Value;

	this->Mag = sqrtf(X * X + Y * Y);

	this->DirectionAngle = atan2f(Y, X);
	if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);
}


void Vector2D ::operator/=(const float& Value)
{
	this->X /= Value;
	this->Y /= Value;

	this->Mag = sqrtf(X * X + Y * Y);

	this->DirectionAngle = atan2f(Y, X);
	if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);
}


void Vector2D ::operator =(const Vector2D& RHS)
{
	X = RHS.X;
	Y = RHS.Y;
	DirectionAngle = RHS.DirectionAngle;
	Mag = RHS.Mag;
	From_X = RHS.From_X;
	From_Y = RHS.From_Y;
	To_X = RHS.To_X;
	To_Y = RHS.To_Y;
	IsInDegree = RHS.IsInDegree;
}

//-----------------------------------------------------------------------------------------------------


//Section-2 
void Vector2D::Normalize()
{
	Mag = sqrtf((X * X) + (Y * Y));

	X = this->X / this->Mag;
	Y = this->Y / this->Mag;

	Mag = sqrtf((X * X) + (Y * Y));
}

void Vector2D::RadiansTo_Degree()
{

	if (!IsInDegree)
		DirectionAngle *= RadiansToDegrees;

	IsInDegree = true;
}

void Vector2D::DegreesTo_Radians()
{

	if (IsInDegree)
		DirectionAngle *= DegreesToRadians;

	IsInDegree = false;

}



//-----------------------------------------------------------------------------------------------------



//Section-3
void Vector2D::Add_InEach(const float& Value)
{
	X += Value;
	Y += Value;

	Mag = sqrtf((X * X) + (Y * Y));

	DirectionAngle = atan2f(Y, X);    //Converts to Radian

	if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);
}


void Vector2D::Subtract_InEach(const float& Value)
{
	X -= Value;
	Y -= Value;


	Mag = sqrtf((X * X) + (Y * Y));


	DirectionAngle = atan2f(Y, X);          //Converts to Radian
	if ((X < 0.0f && Y < 0.0f) || (X > 00.0f && Y < 0.0f))DirectionAngle = DirectionAngle + (2.0f * 3.1415f);
}


void Vector2D::AngleChange_InDegrees(const float& Angle_InDegree)
{
	if (!IsInDegree)
		this->RadiansTo_Degree();

	float Angl = Angle_InDegree;

	if (Angle_InDegree >= 360)
	{
		
		float i = Angle_InDegree / 360.0f;

		Angl -= (i * 360.0f);
	}

	DirectionAngle += Angl;

	if (DirectionAngle <=-360.0f)
	{
		float i = DirectionAngle / 360.0f;

		DirectionAngle += (i * 360.0f);
	
		DirectionAngle += 360.0f;

	}

	if (DirectionAngle<0.0f && DirectionAngle>-360.0f)
	{
		DirectionAngle += 360.0f;
	}


	X = (Mag * cos(DirectionAngle*DegreesToRadians)) + From_X;
	Y = (Mag * sin(DirectionAngle*DegreesToRadians)) + From_Y;

	
}


void Vector2D::AngleChange_InRadians(const float& Angle_InRadian)
{
	if (IsInDegree)
		this->DegreesTo_Radians();

	float Angl = Angle_InRadian;

	if (Angle_InRadian >= 6.283f)
	{

		float i = Angle_InRadian / 6.283f;

		Angl -= (i * 6.283f);
	}

	DirectionAngle += Angl;

	if (DirectionAngle <= -6.283f)
	{
		float i = DirectionAngle / 6.283f;

		DirectionAngle += (i * 6.283f);

		DirectionAngle += 6.283f;

	}

	if (DirectionAngle<0.0f && DirectionAngle>-6.283f)
	{
		DirectionAngle += 6.283f;
	}


	X = (Mag * cos(DirectionAngle)) + From_X;
	Y = (Mag * sin(DirectionAngle)) + From_Y;
}





//--------------------------------------------------------------------------------------------------------------------




//Section-4
Vector2D Vector2D::ParallelogramAddition(const Vector2D& Second_Vector)
{	
	float SecondAngle = Second_Vector.DirectionAngle;

	this->DegreesTo_Radians();

	if (Second_Vector.IsInDegree)SecondAngle = SecondAngle * DegreesToRadians;


	float XMag = this->Mag * cosf(this->DirectionAngle) + Second_Vector.Mag * cosf(SecondAngle);
	float YMag = this->Mag * sinf(this->DirectionAngle) + Second_Vector.Mag * sinf(SecondAngle);

	Vector2D Resultant;

	Resultant.Mag = sqrtf(((this->Mag * this->Mag) + (Second_Vector.Mag * Second_Vector.Mag) + 2 * this->Mag * Second_Vector.Mag * cosf(fabsf(this->DirectionAngle - SecondAngle))));

	Resultant.DirectionAngle = atan2f(YMag, XMag);

	if (Resultant.DirectionAngle <= 0.0f)Resultant.DirectionAngle += 2.0f * 3.1415f;

	Resultant.X = Resultant.Mag * cosf(Resultant.DirectionAngle);
	Resultant.Y = Resultant.Mag * sinf(Resultant.DirectionAngle);

	return Resultant;
}












//======================================================

//PHYSICS IMPLEMENTATION

//0 ->   CLASS----------->  TIME  ---

//Private Functions
int Physic::Time::TimeToNumber()
{
	return ((60 * 60 * iHours) + (60 * iMinutes) + iSeconds);
}

void Physic::Time::NumberToTime(const int Number)
{
	if (Number > 0)
	{
		int min = 0, hor = 0;
		int min_t = Number / 60;
		int sec = Number % 60;

		if (min_t > 59)
		{
			min = min_t % 60;
			hor = min_t / 60;
		}
		else
		{
			min = min_t;
			hor = 0;
		}

		iHours = hor;
		iMinutes = min;
		iSeconds = sec;
	}
	else
	{
		iHours = 0;
		iMinutes = 0;
		iSeconds = 0;
	}
}


//Operator Functions
void Physic::Time::operator +=( Time& RHS)
{
	int Rhs = RHS.TimeToNumber();
	int Self = this->TimeToNumber();

	Self = Self + Rhs;

	this->NumberToTime(Self);
}

void Physic::Time::operator -=(Time& RHS)
{
	int Rhs = RHS.TimeToNumber();
	int Self = this->TimeToNumber();

	if (Rhs >= Self)
	{
		this->iSeconds = 0;
		this->iMinutes = 0;
		this->iSeconds = 0;
		
		return;
	}
	else if (Rhs < Self)
	{
		Self = Self - Rhs;
	}
	this->NumberToTime(Self);
	return;
}

void Physic::Time::operator *=(const int& Value)
{
	if (Value >= 0)
	{
		int Self = this->TimeToNumber();
		Self = Self * Value;
		this->NumberToTime(Self);
	}
}

void Physic::Time::operator /=(const int& Value)
{
	if (Value > 0)
	{
		int Self = this->TimeToNumber();
		Self = Self / Value;
		if (Self <= 0)
		{
			iSeconds = 0;
			iHours = 0;
			iMinutes = 0;
		}
		else
		{
			this->NumberToTime(Self);
		}


	}
}


///////
Physic::Time Physic::Time::operator + (Time& RHS)
{
	Time Result;
	int Total = this->TimeToNumber() + RHS.TimeToNumber();

	Result.NumberToTime(Total);

	return Result;
}

Physic::Time Physic::Time::operator - (Time& RHS)
{
	Time Result;
	if (this->TimeToNumber() <= RHS.TimeToNumber())
	{
		return Result;
	}
	else if(this->TimeToNumber()>RHS.TimeToNumber())
	{
		int Total = this->TimeToNumber() - RHS.TimeToNumber();

		Result.NumberToTime(Total);

		return Result;
	}
	return Result;
}

Physic::Time Physic::Time::operator *(const int& Value)
{
	Time Result;
	if (Value >= 0)
	{
	
		int Total = this->TimeToNumber() * Value;

		Result.NumberToTime(Total);

		return Result;
	}
	return Result;
}

Physic::Time Physic::Time::operator/(const int& Value)
{
	Time Result;

	if (Value > 0)
	{
		int Self = this->TimeToNumber();
		Self = Self / Value;
		if (Self <= 0)
		{
			return Result;
		}

		Result.NumberToTime(Self);

		return Result;
	}

	return Result;
}


//Arithmatic Functions

void Physic::Time::AddIn_Seconds(const int& Value)
{
	if (Value > 0)
	{
		int Self = this->TimeToNumber();
		Self = Self + Value;
		this->NumberToTime(Self);
	}
}

void Physic::Time::AddIn_Minutes(const int& Value)
{
	if (Value > 0)
	{
		int Self = (iHours * 60) + iMinutes;
		Self = Self + Value;

		iMinutes = Self % 60;
		iHours = Self / 60;
	}
}

void Physic::Time::AddIn_Hours(const int& Value)
{
	if(Value>0)
	iHours = iHours + Value;
}


void Physic::Time::SubtractFrom_Seconds(const int& Value)
{
	if (Value > 0)
	{
		int Self = this->TimeToNumber();
		if (Self >= Value)
			Self = Self - Value;
		else Self = 0;
		this->NumberToTime(Self);
	}
}

void Physic::Time::SubtractFrom_Minutes(const int& Value)
{
	if (Value > 0)
	{
		if (Value < ((iHours*60)+iMinutes))
		{
			int Self = ((iHours * 60) + iMinutes);
			Self = Self - Value;
			iMinutes = Self % 60;
			iHours = Self / 60;
		}
		else
		{
			iMinutes = 0;
			iHours = 0;
		}
	}
}

void Physic::Time::SubtractFrom_Hours(const int& Value)
{
	if (Value < iHours)
	{
		iHours = iHours - Value;
	}
	else
	{
		iHours = 0;
	}
}


////////////

void Physic::Time::AddIn_FSeconds(const float& Value)
{
	fSeconds += Value;
	int Self = fSeconds;
	this->NumberToTime(Self);
}

void Physic::Time::SubtractFrom_FSeconds(const float& Value)
{
	if (fSeconds > Value)
	{
		fSeconds -= Value;
		int Self = fSeconds;
		this->NumberToTime(Self);
	}
	else
	{
		fSeconds = 0.0f;
		this->NumberToTime(0);
	}
}

//1->           CLASS------->        Particles  ----------  Base Class



void Physic::Particles::SetAccleration(float Magnitude, const Vector2D& Direction)
{
	Accleration = Direction;

	Accleration.Normalize();

	Accleration *= Magnitude;


}

void Physic::Particles::Acclerate(const float& fElapsedTime)
{
	Velocity += Accleration * fElapsedTime;
}

void Physic::Particles::Move_With_IncreasingAcc(const float& fElapsedTime)
{
	Velocity += Accleration * fElapsedTime;

	ParPos.fX += Velocity.GetMagnitude() * fElapsedTime * cosf(Velocity.GetDirection());
	ParPos.fY += Velocity.GetMagnitude() * fElapsedTime * sinf(Velocity.GetDirection());

	ParPos.iX = ParPos.fX;
	ParPos.iY = ParPos.fY;
}

void Physic::Particles::Set_Velocity(float Magnitude, const Vector2D& Direction)
{	
	Velocity = Direction;
	Velocity.Normalize();
	Velocity *= Magnitude;
}

void Physic::Particles::Update_Position(const float& fElapsedTime)
{

	ParPos.fX += Velocity.GetMagnitude() * fElapsedTime * cosf(Velocity.GetDirection());
	ParPos.fY += Velocity.GetMagnitude() * fElapsedTime * sinf(Velocity.GetDirection());

	ParPos.iX = ParPos.fX;
	ParPos.iY = ParPos.fY;
}


//2->           CLASS------->       Neutral-Particles   Derived Virtually From Base Class Particles


void Physic::Neutral_Particles::Update_ParticlePhysic( const Position& Bottom_Ground)
{
	Height = Bottom_Ground.iY - ParPos.iY;
	KineticEnergy = 1 / 2 * Mass * Velocity.GetMagnitude() * Velocity.GetMagnitude();
	PotentialEnergy = Mass * Height * 9.81f;

	Momentum = Velocity;
	Momentum.Normalize();
	Momentum *= Mass * Velocity.GetMagnitude();

}




//3->           CLASS------->       Plane2D  Derived Virtually From Base Class RigidBody

void Physic::Plane2D::Set_AngularDisplacement_InRad(const float& Value, bool AntiClockWise)
{
	if (Value > 0.0f)
	{
		Angular_Displacement.Direction = AntiClockWise;
		Angular_Displacement.Magnitude = Value;
	}
}

void Physic::Plane2D::Set_AngularVelocity_InRad(const float& Value, bool AntiClockWise)
{
	if (Value > 0.0f)
	{
		Angular_Veloctiy.Direction = AntiClockWise;
		Angular_Veloctiy.Magnitude = Value;
	}
}

void Physic::Plane2D::Set_AngularAccleration_InRad(const float& Value, bool AntiClockWise)
{
	if (Value > 0.0f)
	{
		Angular_Accleration.Magnitude = Value;
		Angular_Accleration.Direction = AntiClockWise;
	}
}

void Physic::Plane2D::Update_Rotation(const float& fElaspedTime)
{
	if (Angular_Accleration.Direction == RotationalMec::ClockWise)
	{
		Angular_Veloctiy.Magnitude = Angular_Accleration.Magnitude * fElaspedTime;
		Angular_Displacement.Magnitude += Angular_Veloctiy.Magnitude * fElaspedTime;
	}
	else if (Angular_Accleration.Direction == RotationalMec::AntiClockWise)
	{
		Angular_Veloctiy.Magnitude = Angular_Accleration.Magnitude * fElaspedTime;
		Angular_Displacement.Magnitude -= Angular_Veloctiy.Magnitude * fElaspedTime;
	}
}

void Physic::Plane2D::Draw(M_CHARS* Screen, const  Generic_Vector<int>& Screen_Resolution, const M_CHARS& PLaneSymbol)
{
	if (!PovitPointSet)return;
	else
	{
		switch (PovitPoint)
		{
		case Center:
		{
			
			Position TempLeft, TempRight;
			Position Right,Left;         //Left Side of Origin of Line and Right Side Of Origin Line Coord
			
			int Upper = 0, Lower = 0;
			if (iHeight % 2 == 1)
			{
				Upper = iHeight / 2+1;
				Lower = iHeight / 2;
			}
			else if (iHeight % 2 == 0)
			{
				Upper = iHeight / 2;
				Lower = iHeight / 2;
			}


			//ERASE FROM PREVIOUS ANGULAR POSITION
			Right.fX = iWidth/2 * cosf(PreviousAngularDisplacement_ToDraw) + ParPos.fX;
			Right.fY = iWidth/2 * sinf(PreviousAngularDisplacement_ToDraw) + ParPos.fY;

			Right.iX = Right.fX;
			Right.iY = Right.fY;

			Left.fX = iWidth / 2 * cosf(PreviousAngularDisplacement_ToDraw +3.1415f) + ParPos.fX;
			Left.fY = iWidth / 2 * sinf(PreviousAngularDisplacement_ToDraw +3.1415f) + ParPos.fY;

			Left.iX =Left.fX ;
			Left.iY = Left.fY;

			DrawLine(Screen, Screen_Resolution, Left, Right, PLaneSymbol);

			TempLeft.fX =Left.fX;
			TempLeft.fY = Left.fY;

			TempRight.fX = Right.fX;
			TempRight.fY = Right.fY;


			


			//FIRST FOR LOOP TO UPPER SIDE RECT
			
			for (int i = 0;i < Upper;i++)
			{
				TempLeft.fX += cosf(PreviousAngularDisplacement_ToDraw +1.5707f);
				TempLeft.fY += sinf(PreviousAngularDisplacement_ToDraw +1.5707f);

				TempRight.fX += cosf(PreviousAngularDisplacement_ToDraw +1.5707f);
				TempRight.fY += sinf(PreviousAngularDisplacement_ToDraw +1.5707f);

				TempLeft.iX = TempLeft.fX;
				TempLeft.iY = TempLeft.fY;

				TempRight.iX = TempRight.fX;
				TempRight.iY = TempRight.fY;

				DrawLine(Screen, Screen_Resolution, TempLeft, TempRight, L' ');
			}
						
			//READJUST THE ORIGINAL POSITION
			TempLeft.fX = Left.fX;
			TempLeft.fY = Left.fY;

			TempRight.fX = Right.fX;
			TempRight.fY = Right.fY;


			//SECOND FOR LOOP TO LOWER SIDE RECT
			for (int i = 0;i < Lower;i++)
			{
				TempLeft.fX += cosf(PreviousAngularDisplacement_ToDraw + 4.7121f);
				TempLeft.fY += sinf(PreviousAngularDisplacement_ToDraw + 4.7121f);

				TempRight.fX += cosf(PreviousAngularDisplacement_ToDraw + 4.7121f);
				TempRight.fY += sinf(PreviousAngularDisplacement_ToDraw + 4.7121f);

				TempLeft.iX = TempLeft.fX;
				TempLeft.iY = TempLeft.fY;

				TempRight.iX = TempRight.fX;
				TempRight.iY = TempRight.fY;

				DrawLine(Screen, Screen_Resolution, TempLeft, TempRight,L' ');
			}

			PreviousAngularDisplacement_ToDraw = Angular_Displacement.Magnitude;
			
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//REDRAW AT NEW ANGULAR POSITION


			Right.fX = iWidth/2 * cosf(Angular_Displacement.Magnitude) + ParPos.fX;
			Right.fY = iWidth/2 * sinf(Angular_Displacement.Magnitude) + ParPos.fY;

			Right.iX = Right.fX;
			Right.iY = Right.fY;

			Left.fX = iWidth / 2 * cosf(Angular_Displacement.Magnitude +3.1415f) + ParPos.fX;
			Left.fY = iWidth / 2 * sinf(Angular_Displacement.Magnitude +3.1415f) + ParPos.fY;

			Left.iX =Left.fX+1;
			Left.iY = Left.fY;

			DrawLine(Screen, Screen_Resolution, Left, Right, PLaneSymbol);

			TempLeft.fX =Left.fX;
			TempLeft.fY = Left.fY;

			TempRight.fX = Right.fX;
			TempRight.fY = Right.fY;

			
			//FIRST FOR LOOP TO UPPER SIDE RECT
			
			for (int i = 0;i < Upper;i++)
			{
				TempLeft.fX += cosf(Angular_Displacement.Magnitude +1.5707f);
				TempLeft.fY += sinf(Angular_Displacement.Magnitude +1.5707f);

				TempRight.fX += cosf(Angular_Displacement.Magnitude +1.5707f);
				TempRight.fY += sinf(Angular_Displacement.Magnitude +1.5707f);

				TempLeft.iX = TempLeft.fX;
				TempLeft.iY = TempLeft.fY;

				TempRight.iX = TempRight.fX;
				TempRight.iY = TempRight.fY;

				DrawLine(Screen, Screen_Resolution, TempLeft, TempRight, PLaneSymbol);
			}
						
			//READJUST THE ORIGINAL POSITION
			TempLeft.fX = Left.fX;
			TempLeft.fY = Left.fY;

			TempRight.fX = Right.fX;
			TempRight.fY = Right.fY;


			//SECOND FOR LOOP TO LOWER SIDE RECT
			for (int i = 0;i < Lower;i++)
			{
				TempLeft.fX += cosf(Angular_Displacement.Magnitude + 4.77521f);
				TempLeft.fY += sinf(Angular_Displacement.Magnitude + 4.77521f);

				TempRight.fX += cosf(Angular_Displacement.Magnitude + 4.77521f);
				TempRight.fY += sinf(Angular_Displacement.Magnitude + 4.77521f);

				TempLeft.iX = TempLeft.fX;
				TempLeft.iY = TempLeft.fY;

				TempRight.iX = TempRight.fX ;
				TempRight.iY = TempRight.fY;

				DrawLine(Screen, Screen_Resolution, TempLeft, TempRight, PLaneSymbol);
			}

			break;
		}
		case BottomLeft:
		{
			
			Position TempLeft, TempRight;
			Position Right;


			//----------------THIS IS For Erasing Previous Position------------------
			Right.fX = iWidth * cosf(PreviousAngularDisplacement_ToDraw)+ParPos.fX;
			Right.fY = iWidth * sinf(PreviousAngularDisplacement_ToDraw)+ParPos.fY;

			Right.iX = Right.fX;
			Right.iY = Right.fY;

			DrawLine(Screen, Screen_Resolution,ParPos, Right, PLaneSymbol);
			
			
			TempLeft.fX = ParPos.fX;
			TempLeft.fY = ParPos.fY;

			TempRight.fX = Right.fX;
			TempRight.fY = Right.fY;

			
			for (int i = ParPos.iY+1 ;i < ParPos.iY + iHeight;i++)
			{

				TempLeft.fX += cosf(PreviousAngularDisplacement_ToDraw+ 4.7121f);
				TempLeft.fY += sinf(PreviousAngularDisplacement_ToDraw+ 4.7121f);

				TempRight.fX +=  cosf(PreviousAngularDisplacement_ToDraw+ 4.7121f);
				TempRight.fY +=  sinf(PreviousAngularDisplacement_ToDraw+ 4.7121f) ;

				TempLeft.iX = TempLeft.fX;
				TempLeft.iY = TempLeft.fY;

				TempRight.iX = TempRight.fX;
				TempRight.iY = TempRight.fY;

				
				DrawLine(Screen, Screen_Resolution, TempLeft, TempRight, L' ');
			}


			//Stores Values Of Previous Position
			PreviousAngularDisplacement_ToDraw = Angular_Displacement.Magnitude;
			
			
			
			////////////////

			//REDRAWS AT NEW POSITION

			Right.fX = iWidth * cosf(Angular_Displacement.Magnitude) + ParPos.fX;
			Right.fY = iWidth * sinf(Angular_Displacement.Magnitude) + ParPos.fY;

			Right.iX = Right.fX;
			Right.iY = Right.fY;

			DrawLine(Screen, Screen_Resolution, ParPos, Right, PLaneSymbol);


			TempLeft.fX = ParPos.fX;
			TempLeft.fY = ParPos.fY;

			TempRight.fX = Right.fX;
			TempRight.fY = Right.fY;


			for (int i = ParPos.iY + 1;i < ParPos.iY + iHeight;i++)
			{

				TempLeft.fX += cosf(Angular_Displacement.Magnitude + 4.7121f);
				TempLeft.fY += sinf(Angular_Displacement.Magnitude + 4.7121f);

				TempRight.fX += cosf(Angular_Displacement.Magnitude + 4.7121f);
				TempRight.fY += sinf(Angular_Displacement.Magnitude + 4.7121f);

				TempLeft.iX = TempLeft.fX;
				TempLeft.iY = TempLeft.fY;

				TempRight.iX = TempRight.fX;
				TempRight.iY = TempRight.fY;


				DrawLine(Screen, Screen_Resolution, TempLeft, TempRight, PLaneSymbol);
			}


			break;
		}
		default:
			break;
		}
	}
}

//======================================================

//MATHS IMPLEMENTATION












//======================================================
//======================================================
//=============END++++END++++END++++END++++END===========
