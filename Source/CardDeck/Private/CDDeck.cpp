// Copyright James Lennon


#include "CDDeck.h"


UCDDeck::UCDDeck()
{
}

void UCDDeck::CreateNewDeck(const bool bUseJokers)
{
	StandardDeck = ConstructDeck(bUseJokers);

	RefreshDeck();
}

void UCDDeck::RefreshDeck()
{
	for(int32 i = 0; i < StandardDeck.Num(); i++)
	{
		StandardDeck[i].RefreshCard();
	}
}

TArray<FCard> UCDDeck::ConstructDeck(const bool bUseJokers)
{
	TArray<FCard> Result;

	for(int32 NewCardValue = 0; NewCardValue < static_cast<int32>(ECardValue::Joker); NewCardValue++)
	{
		for(int32 NewCardSuit = 0; NewCardSuit < static_cast<int32>(ECardSuit::MAX); NewCardSuit++)
		{						
			Result.Add(FCard(static_cast<ECardSuit>(NewCardSuit), static_cast<ECardValue>(NewCardValue)));
		}
	}

	// TODO: Allow a custom amount
	if(bUseJokers)
	{
		for(int32 i = 0; i < 2; i++)
		{			
			Result.Add( FCard(ECardSuit::MAX, ECardValue::Joker));
		}
	}

	return Result;
}

TArray<FCard> UCDDeck::GetStandardDeck() const
{
	return StandardDeck;
}


void UCDDeck::ShuffleDecks()
{
	StandardDeck.Sort([](const FCard& A, const FCard& B)
	{
		return A.GetID() < B.GetID();
	});
}

bool UCDDeck::DrawCard(const int32 NumberToDraw, TArray<FCard>& OutCards)
{
	OutCards.Empty();

	for(int32 i = 0; i < NumberToDraw; i++)
	{
		if(StandardDeck.IsValidIndex(0))
		{
			OutCards.Add(StandardDeck.Pop());
		}
		else
		{
			return false;
		}
	}

	return true;
}

void UCDDeck::PrintCards()
{
	for(int32 i = 0; i < StandardDeck.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("S %d: %s"), i, *StandardDeck[i].ToString())
	}
}
