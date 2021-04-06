// Copyright James Lennon

#pragma once

#include "CoreMinimal.h"
#include "CDCard.h"
#include "CDDeck.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CARDDECK_API UCDDeck : public UObject
{
	GENERATED_BODY()

public:
	UCDDeck();

	/**
	* Creates a new deck for the standard and joker slots 
	*
	* @param bUseJokers Whether or not to add jokers 
	*/
	UFUNCTION(BlueprintCallable, Category="Card Deck")
	void CreateNewDeck(bool bUseJokers = false);

	// Generates a new FGuid for each card for shuffling to be different
	UFUNCTION(BlueprintCallable, Category="Card Deck")
	void RefreshDeck();

	// Creates one deck with no jokers
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Card Deck")
	static TArray<FCard> ConstructDeck(bool bUseJokers);


	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Card Deck")
	TArray<FCard> GetStandardDeck() const;

	UFUNCTION(BlueprintCallable, Category="Card Deck")
	void ShuffleDecks();

	/**
	* Draws the given number of cards and removes them from the deck 
	*
	* @param NumberToDraw How many cards to draw
	* @param OutCards The newly drawn cards
	* @returns If it was able to draw the number of cards. 
	*/
	UFUNCTION(BlueprintCallable, Category="Card Deck")
	bool DrawCard(int32 NumberToDraw, TArray<FCard>& OutCards);
	

private:

	void PrintCards();

	// TODO: For the future, create a generic constructor interface or something to allow for other deck setups

	/*
	 * Static constructors or lookup tables cannot be used for the actual card ID generation because of how FGUIDs work
	 */
	TArray<FCard> StandardDeck;

	TArray<FCard> StandardDeckDiscard;
};
