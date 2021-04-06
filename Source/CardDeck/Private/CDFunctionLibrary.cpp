// Copyright James Lennon


#include "CDFunctionLibrary.h"


bool UCDFunctionLibrary::EqualEqual_CardCard(const FCard& A, const FCard& B)
{
	return A == B;
}

bool UCDFunctionLibrary::EqualEqual_CardCardValue(const FCard& A, const FCard& B)
{
	return A.CardValue & B.CardValue;
}

bool UCDFunctionLibrary::EqualEqual_CardCardSuit(const FCard& A, const FCard& B)
{
	return A.CardSuit & B.CardSuit;
}
