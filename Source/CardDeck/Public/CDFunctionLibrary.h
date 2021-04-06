// Copyright James Lennon

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CDCard.h"
#include "CDDeck.h"
#include "CDFunctionLibrary.generated.h"

#define TO_FLAG(Enum) (1 << static_cast<uint8>(Enum))


/**
 * 
 */
UCLASS()
class CARDDECK_API UCDFunctionLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Returns true if the cards are equal (A == B)
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Equal Card", CompactNodeTitle = "==", Keywords = "== equal"), Category="Card Deck")
	static bool EqualEqual_CardCard(const FCard& A, const FCard& B);

	// Returns true if the card values are equal (A.Queen == B.Queen)
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Equal Card Value", CompactNodeTitle = "V == V", Keywords = "== equal"), Category="Card Deck")
    static bool EqualEqual_CardCardValue(const FCard& A, const FCard& B);

	// Returns true if the card suits are equal (A.Diamond == B.Diamond)
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Equal Card Suit", CompactNodeTitle = "S == S", Keywords = "== equal"), Category="Card Deck")
    static bool EqualEqual_CardCardSuit(const FCard& A, const FCard& B);
};


//