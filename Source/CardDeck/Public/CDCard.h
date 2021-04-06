// Copyright James Lennon

#pragma once

#include "CoreMinimal.h"
#include "CDCard.generated.h"

#define TO_FLAG(Enum) (1 << static_cast<uint8>(Enum))
#define TO_ENUM(BitMask, Enum) (static_cast<Enum>(BitMask))

template<typename T>
static FORCEINLINE FString EnumToString(const FString& EnumName, const T Value)
{
	UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName);
	return *(Enum ? Enum->GetNameStringByIndex(static_cast<uint8>(Value)) : "null");
}

template <typename T>
static FORCEINLINE T StringToEnum(const FString& EnumName, const FString& String)
{
	UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
	return static_cast<T>(!Enum ? 0 : Enum->GetIndexByName(FName(*String)));
}

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ECardSuit : uint8
{
	Diamond,
	Club,
	Heart,
	Spade,

	// Used for iterating
    MAX UMETA(Hidden)
};
ENUM_CLASS_FLAGS(ECardSuit);


// Ace can be low or high depending on the game so it's the first element to make it easier to work with
UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ECardValue : uint8
{
	Ace,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Joker,

	// Used for iterating
	MAX UMETA(Hidden)
};
ENUM_CLASS_FLAGS(ECardValue);

/**
 * The information for an individual playing card
 */
USTRUCT(BlueprintType)
struct FCard
{
	GENERATED_BODY()

	// This needs to stay up here because of initialization order and should never be exposed to blueprint.
private:
	// Skips the verification check on construction, C++ only
	UPROPERTY()
	bool bUseFastVersions;

public:
	// The suit of the card
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Playing Card", meta = (Bitmask, BitmaskEnum = ECardSuit))
	int32 CardSuit;

	// The card value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Playing Card", meta = (Bitmask, BitmaskEnum = ECardValue))
	int32 CardValue;

	// Is this card high (e.g. Aces high or aces low (default))
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Playing Card")
	bool bIsHigh;
	
protected:
	// GUID that is generated each time the game is run for shuffling purposes
	// This should be read-only at all times (minus debugging)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Playing Card")
	FGuid CardID;
	
public:
	FCard()
		: bUseFastVersions(false)
		, CardSuit(0)
		, CardValue(0)
		, bIsHigh(false)
		, CardID(FGuid())
	{}

	FCard(const ECardSuit& InSuit, const ECardValue& InValue)
		: bUseFastVersions(false)
	    , CardSuit(TO_FLAG(InSuit))
	    , CardValue(TO_FLAG(InValue))
		, bIsHigh(false)
		, CardID(FGuid())
	{
	}

	FCard(const ECardSuit& InSuit, const ECardValue& InValue, const bool bInIsHigh)
		: bUseFastVersions(false)
	    , CardSuit(TO_FLAG(InSuit))
        , CardValue(TO_FLAG(InValue))
		, bIsHigh(bInIsHigh)
		, CardID(FGuid())
	{		
		if(!bUseFastVersions)
		{
			VerifyCard();
		}
	}

	FCard(const ECardSuit& InSuit, const ECardValue& InValue, const bool bInIsHigh, const bool& bInUseFastVersions)
        : bUseFastVersions(bInUseFastVersions)
        , CardSuit(TO_FLAG(InSuit))
        , CardValue(TO_FLAG(InValue))
        , bIsHigh(bInIsHigh)
		, CardID(FGuid())
	{		
		if(!bUseFastVersions)
		{
			VerifyCard();
		}
	}

	FORCEINLINE bool operator==(const FCard& Other) const
	{
		return CardID == Other.CardID;
	}

	// To prevent user error, this makes sure that only JQKA are able to be high
	void VerifyCard()
	{
		static int32 CardFlags = TO_FLAG(ECardValue::Jack) | TO_FLAG(ECardValue::Queen) | TO_FLAG(ECardValue::King) | TO_FLAG(ECardValue::Ace);
		if((CardValue & CardFlags) > 0)
		{
			return;
		}

		bIsHigh = false;
	}

	void RefreshCard()
	{
		CardID = FGuid::NewGuid();
	}

	FGuid GetID() const
	{
		return CardID;
	}

	FString ToString() const
	{
		//const FString ValueString = EnumToString("ECardValue", TO_ENUM(CardValue, ECardValue));
		const FString ValueString = EnumToString("ECardValue", BitmaskToValue(CardValue));
		const FString SuitString = EnumToString("ECardSuit", BitmaskToSuit(CardSuit));
		
		return FString("Suit: " + SuitString + ", Value: " + ValueString);
	}

	/* I am having a lovely time troubleshooting this so manual work it is*/
	
	static ECardSuit BitmaskToSuit(const int32 Bitmask)
	{

		for(int32 i = 0; i < static_cast<int32>(ECardSuit::MAX); i++)
		{
			const ECardSuit Value = static_cast<ECardSuit>(i);
			if(Bitmask & TO_FLAG(Value))
			{
				return Value;
			}
		}
		
		return ECardSuit::MAX;
	}

	static ECardValue BitmaskToValue(const int32 Bitmask)
	{
		for(int32 i = 0; i < static_cast<int32>(ECardValue::MAX); i++)
		{
			const ECardValue Value = static_cast<ECardValue>(i);
			if(Bitmask & TO_FLAG(Value))
			{
				return Value;
			}
		}
		
		return ECardValue::MAX;
	}
};


