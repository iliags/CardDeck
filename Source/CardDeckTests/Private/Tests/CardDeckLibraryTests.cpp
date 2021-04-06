// Copyright Nifty Productions


#include "CDFunctionLibrary.h"
#include "CDCard.h"
#include "Misc/AutomationTest.h"
#include "../ADTestUtils.h"



BEGIN_DEFINE_SPEC(FCardDeckLibraryTests, "CardDeck.FunctionLibrary", FADTestUtils::TestsFlags)

END_DEFINE_SPEC(FCardDeckLibraryTests)


void FCardDeckLibraryTests::Define()
{
	Describe("Equal", [this]()
    {
        It("==", [this]()
        {
        	// The == operator relies on initialized CardID's so this is necessary only here.
            FCard AceSpade = FCard(ECardSuit::Spade, ECardValue::Ace);
        	AceSpade.RefreshCard();
        	
            FCard AceHeart = FCard(ECardSuit::Heart, ECardValue::Ace);
        	AceHeart.RefreshCard();
            
            TestTrue("Execute", UCDFunctionLibrary::EqualEqual_CardCard(AceSpade, AceSpade));
            TestFalse("Execute", UCDFunctionLibrary::EqualEqual_CardCard(AceSpade, AceHeart));
        });

		It("V == V", [this]()
        {
		    const FCard AceSpade = FCard(ECardSuit::Spade, ECardValue::Ace);
            const FCard AceHeart = FCard(ECardSuit::Heart, ECardValue::Ace);
			
            TestTrue("Execute", UCDFunctionLibrary::EqualEqual_CardCardValue(AceSpade, AceHeart));
        });

		It("S == S", [this]()
        {
			const FCard AceSpade = FCard(ECardSuit::Spade, ECardValue::Ace);
			const FCard KingSpade = FCard(ECardSuit::Spade, ECardValue::King);
			
            TestTrue("Execute", UCDFunctionLibrary::EqualEqual_CardCardSuit(AceSpade, KingSpade));
        });
    });
}