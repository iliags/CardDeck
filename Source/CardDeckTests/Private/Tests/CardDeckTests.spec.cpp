// Copyright Nifty Productions


#include "CDCard.h"
#include "CDDeck.h"
#include "Misc/AutomationTest.h"
#include "../ADTestUtils.h"


BEGIN_DEFINE_SPEC(FCardDeckTests, "CardDeck.CardDeck", FADTestUtils::TestsFlags)
const FCard AceSpade = FCard(ECardSuit::Spade, ECardValue::Ace);
const FCard AceHeart = FCard(ECardSuit::Heart, ECardValue::Ace);

const FCard KingClub = FCard(ECardSuit::Club, ECardValue::King);
const FCard KingSpade = FCard(ECardSuit::Spade, ECardValue::King);

UCDDeck* Deck = NewObject<UCDDeck>();
END_DEFINE_SPEC(FCardDeckTests)


void FCardDeckTests::Define()
{

	Describe("Card", [this]()
    {
		Describe("Operators", [this]()
		{
			It("==", [this]()
			{
				const FCard AceSpade2 = AceSpade;
				
				TestTrue("Execute", AceSpade == AceSpade2);
			});
		});

		Describe("Functions", [this]()
	    {		
			It("VerifyCard", [this]()
			{
				const FCard OkCard = FCard(ECardSuit::Club, ECardValue::Ace, true);
				const FCard DudCard = FCard(ECardSuit::Club, ECardValue::Five, true);

				TestTrue("Execute", OkCard.bIsHigh == true);
				TestFalse("Execute", DudCard.bIsHigh == true);
	        });
			
			It("VerifyCard Fast Skips Verification", [this]()
	        {
	            const FCard OkCard = FCard(ECardSuit::Club, ECardValue::Ace, true, true);
	            const FCard DudCard = FCard(ECardSuit::Club, ECardValue::Five, true, true);

	            TestTrue("Execute", OkCard.bIsHigh == true);
	            TestTrue("Execute", DudCard.bIsHigh == true);
	        });


			
	    });
    });


	Describe("Deck", [this]()
	{
		BeforeEach([this]()
		{
			TestTrue("Valid Deck Object Creation", IsValid(Deck));
		});

		It("verifies valid no joker deck count", [this]()
		{
			Deck->CreateNewDeck(false);

			TestEqual("Execute", Deck->GetStandardDeck().Num(), 52);
		});

		It("verifies valid joker deck count", [this]()
        {
            Deck->CreateNewDeck(true);

            TestEqual("Execute", Deck->GetStandardDeck().Num(), 54);
        });

		It("verifies that cards can be drawn from none to all from no joker deck", [this]()
        {
			Deck->CreateNewDeck(false);
			const int32 DeckCount = Deck->GetStandardDeck().Num();
			
			for(int32 i = 0; i < DeckCount; i++)
			{
				Deck->CreateNewDeck(false);
				TArray<FCard> DrawnCards;
				const bool bResult = Deck->DrawCard(i, DrawnCards);

				if(bResult)
				{
					TestTrue("Execute", DrawnCards.Num() == i);
				}
				else
				{
					TestTrue("Execute", DrawnCards.Num() < i);
				}
			}
        });

		It("verifies that cards can be drawn from none to all from joker deck", [this]()
        {
            Deck->CreateNewDeck(true);
            const int32 DeckCount = Deck->GetStandardDeck().Num();
			
            for(int32 i = 0; i < DeckCount; i++)
            {
                Deck->CreateNewDeck(false);
                TArray<FCard> DrawnCards;
                const bool bResult = Deck->DrawCard(i, DrawnCards);

                if(bResult)
                {
                    TestTrue("Execute", DrawnCards.Num() == i);
                }
                else
                {
                    TestTrue("Execute", DrawnCards.Num() < i);
                }
            }
        });

		
	});

	/*
	Describe("Deck", [this]()
    {
    });*/
}