#include <time.h>
#include <getopt.h>
#include <stack>
#include <sstream>
#include <array>
#include <map>
#include <assert.h>
#include "sha_utils.h"
#include "sha1.h"
#include "wbs.h"

//the predicate from the old code
bool compare_and_set_0(SHA1 baseSha, SHA1 &newMessage, SHA1 &betterMessage)
{
	if((newMessage.windowWeight_getter() < baseSha.minimalWeight) ||
			(newMessage.firstUnsatisfiedEquation_getter()-1 > baseSha.lastSatisfiedEquationInWindow))
	{
		newMessage.minimalWeight = MIN(newMessage.windowWeight_getter(), baseSha.minimalWeight);
		newMessage.lastSatisfiedEquationInWindow = MAX(newMessage.firstUnsatisfiedEquation_getter()-1,
				baseSha.lastSatisfiedEquationInWindow);
		betterMessage = newMessage;
		return true;
	}
	return false;
}


/*
bool compare_and_update_state_of_conformance_1(SHA1 &newMessage, SHA1 &maximalMessage)
{
	if((newMessage.windowWeight_getter() < maximalMessage.minimalWeight) ||
			(newMessage.firstUnsatisfiedEquation_getter()-1 > maximalMessage.lastSatisfiedEquationInWindow) ||
			((newMessage.windowWeight_getter()== maximalMessage.minimalWeight) &&
					(newMessage.firstUnsatisfiedEquation_getter() > maximalMessage.firstUnsatisfiedEquation_getter()))||
					((newMessage.windowWeight_getter() < maximalMessage.windowWeight_getter()) &&
							(newMessage.windowWeight_getter() == maximalMessage.lastSatisfiedEquationInWindow)))
	{
		if((newMessage.windowWeight_getter() < maximalMessage.minimalWeight))
			newMessage.minimalWeight = newMessage.windowWeight_getter();
		else
			newMessage.minimalWeight = maximalMessage.minimalWeight;
		if(newMessage.firstUnsatisfiedEquation_getter()-1 > maximalMessage.lastSatisfiedEquationInWindow)
			newMessage.lastSatisfiedEquationInWindow = newMessage.firstUnsatisfiedEquation_getter()-1;
		else
			newMessage.lastSatisfiedEquationInWindow = maximalMessage.lastSatisfiedEquationInWindow;
		maximalMessage = newMessage;
#if DEBUG_LOG_LEVEL > 0
		fprintf(gDebugLogFile, "lastSatisfiedEquation=%d windowWeight=%d    maxSatisfiedEquation=%d minimalWeight=%d\n",
					maximalMessage.firstUnsatisfiedEquation_getter()-1, maximalMessage.windowWeight_getter(), maximalMessage.lastSatisfiedEquationInWindow, maximalMessage.minimalWeight);
#endif
		return true;
	}
	return false;
}

bool compare_and_update_state_of_conformance_2(SHA1 &newMessage, SHA1 &maximalMessage)
{
	if((newMessage.windowWeight_getter() < maximalMessage.minimalWeight) &&
			(newMessage.firstUnsatisfiedEquation_getter()-1 > maximalMessage.lastSatisfiedEquationInWindow))
	{
		if((newMessage.windowWeight_getter() < maximalMessage.minimalWeight))
			newMessage.minimalWeight = newMessage.windowWeight_getter();
		else
			newMessage.minimalWeight = maximalMessage.minimalWeight;
		if(newMessage.firstUnsatisfiedEquation_getter()-1 > maximalMessage.lastSatisfiedEquationInWindow)
			newMessage.lastSatisfiedEquationInWindow = newMessage.firstUnsatisfiedEquation_getter()-1;
		else
			newMessage.lastSatisfiedEquationInWindow = maximalMessage.lastSatisfiedEquationInWindow;
		maximalMessage = newMessage;
#if DEBUG_LOG_LEVEL > 0
		fprintf(gDebugLogFile, "lastSatisfiedEquation=%d windowWeight=%d    maxSatisfiedEquation=%d minimalWeight=%d\n",
					maximalMessage.firstUnsatisfiedEquation_getter()-1, maximalMessage.windowWeight_getter(), maximalMessage.lastSatisfiedEquationInWindow, maximalMessage.minimalWeight);
#endif
		return true;
	}
	return false;
}
*/


bool (*compare_and_set)(SHA1, SHA1&, SHA1&) = NULL;

bool greedy_recursion(SHA1 &originalMessage, SHA1& modifiedSoFarMessage,
		const int neutralIndices[], const int numOfIndices, const int nextCorrectionIndex,
		SHA1& maximalMessage, int numOfCorrectionsUsedSoFar, const int greedyRecurseMaxCorrections)
{
	if(nextCorrectionIndex >= numOfIndices)
		return false;

	if(numOfCorrectionsUsedSoFar >= greedyRecurseMaxCorrections)
		return false;

	//check branch without current correction
	if(greedy_recursion(originalMessage, modifiedSoFarMessage, neutralIndices, numOfIndices, nextCorrectionIndex+1,
			maximalMessage, numOfCorrectionsUsedSoFar, greedyRecurseMaxCorrections))
		return true;

	//check branch with current correction
	SHA1 newMessage = modifiedSoFarMessage;
	int equationToCheckNeutrality = originalMessage.firstUnsatisfiedEquation_getter() > LAST_EQUATION_TO_CORRECT ?
			LAST_EQUATION_TO_CORRECT : originalMessage.firstUnsatisfiedEquation_getter();
	originalMessage.disturb_correct_and_test(newMessage, gEquationCorrections[90][neutralIndices[nextCorrectionIndex]].wb[0].wbnl, 0, equationToCheckNeutrality,
			EQUATION_TO_ROUND(originalMessage.firstUnsatisfiedEquation_getter()));
	if(newMessage.firstUnsatisfiedEquation_getter())//??
	{
		//check current branch
		if(compare_and_set(originalMessage, newMessage, maximalMessage))
			return true;
		if(greedy_recursion(originalMessage, newMessage, neutralIndices, numOfIndices,
				nextCorrectionIndex+1, maximalMessage, numOfCorrectionsUsedSoFar+1,
				greedyRecurseMaxCorrections))
			return true;
	}
	return false;
}

void recurse_neutrals_greedy_type(int predicateID)
{
	switch(predicateID)
	{
	case 0:
		compare_and_set = compare_and_set_0;
		break;
//	case 1:
//		compare_and_update_state_of_conformance = compare_and_update_state_of_conformance_1;
//		break;
	}
}

bool recurse_neutrals_greedy(SHA1& baseSha, SHA1& betterMessage, const int greedyRecurseMaxCorrections)
{
	int neutralIndices[MAX_NUMBER_OF_NEUTRALS];
	int numOfIndices = 0;
	for(int i = gNumberOfCorrections[NEUTRALS_CANDIDATES]-1; i > -1; i--)
	{
		SHA1 newMessage = baseSha;
		if(baseSha.disturb_correct_and_test(newMessage, gEquationCorrections[90][i].wb[0].wbnl, 0, NEUTRAL_TRESHOLD, NEUTRAL_TRESHOLD_ROUND))
		{
			if(compare_and_set(baseSha, newMessage, betterMessage))
				return true;
			neutralIndices[numOfIndices++] = i;
			if(numOfIndices > 1)
			{	//TODO: sort the neutrals like in the old code
				if(greedy_recursion(baseSha, newMessage, neutralIndices, numOfIndices-1, 0, betterMessage, 1, greedyRecurseMaxCorrections))
					return true;
			}
		}
	}
	return false;
}


bool recurse_all_neutrals(SHA1& sha, int corrIndex, const int maxNeutralIndexToUse, int neutralsSelectionSoFar, SHA1& resultingSha,
		const int maxNumOfNeutrals)
//recurse first X neutrals tree till finds the first sha above the window and returns
{
	if(corrIndex > maxNeutralIndexToUse)
		return false;

	if(HAMMING(neutralsSelectionSoFar) >= maxNumOfNeutrals)
		return false;

	//skip current correction
	if(recurse_all_neutrals(sha, corrIndex+1, maxNeutralIndexToUse, neutralsSelectionSoFar, resultingSha, maxNumOfNeutrals))
		return true;

	//apply current correction
	int currNeutralsSelection = neutralsSelectionSoFar | BIT_BY_INDEX[corrIndex-1];
	SHA1 newMessage = sha;
	sha.disturb_correct_and_test(newMessage, gEquationCorrections[90][gNumberOfCorrections[NEUTRALS_CANDIDATES]-corrIndex].wb[0].wbnl, 0,
			sha.firstUnsatisfiedEquation_getter(), EQUATION_TO_ROUND(sha.firstUnsatisfiedEquation_getter()));
	if(newMessage.firstUnsatisfiedEquation_getter() < 68)
		return false;
	if(newMessage.current_stage() == ABOVE_97)
	{
		resultingSha = newMessage;
		return true;
	}

	//check the subtree with current correction
	if(recurse_all_neutrals(newMessage, corrIndex+1, maxNeutralIndexToUse, currNeutralsSelection, resultingSha, maxNumOfNeutrals+1))
		return true;

	return false;
}
