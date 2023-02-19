#pragma once

struct UWorldProxy
{
    uint64_t World;
};

struct UEngine
{

};

struct FVector
{
	float X;
	float Y;
	float Z;
};

struct FVector2D
{
	float X;
	float Y;
};

struct FLinearColor
{
	float R;
	float G;
	float B;
	float A;
};

template<class T>
struct TArray
{
	friend struct FString;

public:
	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const
	{
		return Count;
	};

	inline T& operator[](int i)
	{
		return Data[i];
	};

	inline const T& operator[](int i) const
	{
		return Data[i];
	};

	inline bool IsValidIndex(int i) const
	{
		return i < Num();
	}

private:
	T* Data;
	int32_t Count;
	int32_t Max;
};

struct FString : private TArray<wchar_t>
{
	inline FString()
	{
	};

	FString(const wchar_t* other)
	{
		Max = Count = *other ? std::wcslen(other) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* c_str() const
	{
		return Data;
	}

	std::string ToString() const
	{
		auto str1 = std::wstring(Data);
		return std::string(str1.begin(), str1.end());
	}
};

struct FNameEntryId
{
	int32_t Value;
};

struct FName
{
	FNameEntryId ComparisonIndex;
	int32_t Number;
};

struct UObject
{
	void* __vftable;
	int32_t ObjectFlags;
	int32_t InternalIndex;
	void* ClassPrivate;
	FName NamePrivate;
	void* OuterPrivate;

	inline void ProcessEvent(UObject* Function, void* Parms)
	{
		static void(__fastcall* oProcessEvent)(UObject*, UObject*, void*);

		if (!oProcessEvent)
			oProcessEvent = decltype(oProcessEvent)(UObjectBase + 0x204A10); // 40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 30

		oProcessEvent(this, Function, Parms);
	}

	static UObject* StaticFindObject(const wchar_t* InName)
	{
		static UObject* (__fastcall* oStaticFindObject)(UObject*, UObject*, const wchar_t*, bool);
		if (!oStaticFindObject)
			oStaticFindObject = decltype(oStaticFindObject)(UObjectBase + 0x20DC90); // 48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC ? 80 3D -> safe sig, not actual

		return oStaticFindObject(nullptr, (UObject*)-1, InName, false);
	}

	static UObject* FindFunctionChecked(UObject* Object, FName InName)
	{
		static UObject* (__fastcall * oFindFunctionChecked)(UObject*, FName);
		if (!oFindFunctionChecked)
			oFindFunctionChecked = decltype(oFindFunctionChecked)(UObjectBase + 0x1FBC90); // 48 89 5C 24 18 48 89 54 24 10 57

		return oFindFunctionChecked(Object, InName);
	}
};

struct FChunkedFixedUObjectArray
{
    uint64_t Objects;
    uint64_t PreAllocatedObjects;
    int32_t MaxElements;
    int32_t NumElements;
    int32_t MaxChunks;
    int32_t NumChunks;
};
static_assert(sizeof(FChunkedFixedUObjectArray) == 0x20, "size mismatch");

struct FUObjectArray
{
    int32_t ObjFirstGCIndex;
    int32_t ObjLastNonGCIndex;
    int32_t MaxObjectsNotConsideredByGC;
    int32_t OpenForDisregardForGC;
    FChunkedFixedUObjectArray ObjObjects;
    char padding[0x100];
};
static_assert(sizeof(FUObjectArray) == 0x130, "size mismatch");