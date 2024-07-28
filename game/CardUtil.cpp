#include "CardUtil.h"

/*
 * Each of the functions below return a vector used to score a poker holeCards
 * Index 0 represents the type of the poker holeCards (1-9) with 9 being the strongest holeCards: a straight flush
 * The remaining indices are card values necessary to tiebreak between equal type hands
 */

/*
 * Straight Flush (9)
 * Example: 10♦, 9♦, 8♦, 7♦, 6♦
 * Tiebreaker: highest card value
 */
vector<int> CardUtil::scoreStraightFlush(vector<Card> cards) {
    vector<char> suits;
    vector<int> values;
    for (auto card : cards) {
        suits.push_back(card.suit);
        values.push_back(card.value);
    }

    if (!equal(suits.begin() + 1, suits.end(), suits.begin())) return {};
    sort(values.begin(), values.end());

    // Ace can be used as a 1 in straights
    if (values == vector<int>{2, 3, 4, 5, 14}) {
        return {9, 5};
    }

    for (int i = 1; i < values.size(); i++) {
        if (values[i] != values[i-1] + 1) return {};
    }

    return {9, values[4]};
}

/*
 * Quads (8)
 * Example: Q♣, Q♦, Q♥, Q♠, 4♣
 * Tiebreaker: highest value of quads
 */
vector<int> CardUtil::scoreFourOfAKind(vector<Card> cards) {
    map<int, int> valueCount;
    for (auto card : cards) {
        valueCount[card.value]++;
    }

    for (auto [value, count] : valueCount) {
        if (count == 4) {
            return {8, value};
        }
    }
    return {};
}

/*
 * Full House (7)
 * Example: A♦, A♥, A♠, 2♣, 2♥
 * Tiebreaker: highest value of trips, then pairs
 */
vector<int> CardUtil::scoreFullHouse(vector<Card> cards) {
    map<int, int> valueCount;
    for (auto card : cards) {
        valueCount[card.value]++;
    }

    int triple = -1, pair = -1;
    for (auto [value, count] : valueCount) {
        if (count == 3) triple = value;
        if (count == 2) pair = value;
    }

    if (triple != -1 && pair != -1) {
        return {7, triple, pair};
    }
    return {};
}

/*
 * Flush (6)
 * Example: K♣, J♣, 7♣, 5♣, 3♣
 * Tiebreaker: highest card value
 */
vector<int> CardUtil::scoreFlush(vector<Card> cards) {
    vector<char> suits;
    vector<int> values;
    for (auto card : cards) {
        suits.push_back(card.suit);
        values.push_back(card.value);
    }

    if (!equal(suits.begin() + 1, suits.end(), suits.begin())) return {};
    sort(values.begin(), values.end());

    return {6, values[4], values[3], values[2], values[1], values[0]};
}

/*
 * Straight (5)
 * Example: 10♣, 9♦, 8♥, 7♠, 6♣
 * Tiebreaker: highest card value
 */
vector<int> CardUtil::scoreStraight(vector<Card> cards) {
    vector<int> values;
    for (auto card : cards) {
        values.push_back(card.value);
    }
    sort(values.begin(), values.end());

    // Ace can be used as a 1 in straights
    if (values == vector<int>{2, 3, 4, 5, 14}) {
        return {5, 5};
    }

    for (int i = 1; i < values.size(); i++) {
        if (values[i] != values[i-1] + 1) return {};
    }
    return {5, values[4]};
}

/*
 * Trips (4)
 * Example: Q♣, Q♦, Q♥, 8♠, 2♠
 * Tiebreaker: highest value of trips, then highest card
 */
vector<int> CardUtil::scoreThreeOfAKind(vector<Card> cards) {
    vector<int> values;
    map<int, int> valueCount;
    for (auto card : cards) {
        values.push_back(card.value);
        valueCount[card.value]++;
    }

    int trips = -1;
    for (auto [value, count] : valueCount) {
        if (count == 3) trips = value;
    }

    // Remove trips for tiebreaker consideration
    for (int i=0; i<values.size(); i++) {
        if (values[i] == trips) {
            values.erase(values.begin() + i);
        }
    }
    sort(values.begin(), values.end());

    if (trips != -1) {
        return {4, trips, values[1], values[0]};
    }
    return {};
}

/*
 * Two Pair (3)
 * Example: 9♣, 9♦, 5♥, 5♥, 4♠
 * Tiebreaker: highest value of pairs, then highest value of last pair, then highest last card
 */
vector<int> CardUtil::scoreTwoPairs(vector<Card> cards) {
    map<int, int> valueCount;
    for (auto card : cards) {
        valueCount[card.value]++;
    }

    int pairCounter = 0;
    int lastCard;
    vector<int> pairValues;
    for (auto [value, count] : valueCount) {
        if (count == 2) {
            pairCounter += 1;
            pairValues.push_back(value);
        } else {
            lastCard = value;
        }
    }
    sort(pairValues.begin(), pairValues.end());

    if (pairCounter == 2) {
        return {3, pairValues[1], pairValues[0], lastCard};
    }
    return {};
}

/*
 * Pair (2)
 * Example: A♣, A♦, J♥, 10♥, 6♥
 * Tiebreaker: highest value of pair, then highest card of last 3
 */
vector<int> CardUtil::scoreOnePair(vector<Card> cards) {
    vector<int> values;
    map<int, int> valueCount;
    for (auto card : cards) {
        values.push_back(card.value);
        valueCount[card.value]++;
    }

    int pair = -1;
    for (auto [value, count] : valueCount) {
        if (count == 2) {
            pair = value;
        }
    }

    // Remove pair for tiebreaker consideration
    for (int i=0; i<values.size(); i++) {
        if (values[i] == pair) {
            values.erase(values.begin() + i);
        }
    }
    sort(values.begin(), values.end());

    if (pair != -1) {
        return {2, pair, values[2], values[1], values[0]};
    }
    return {};
}

/*
 * High Card "Nothing" (1)
 * Example: 9♣, 8♣, 6♦, 3♦, 2♥
 */
vector<int> CardUtil::scoreHighCard(vector<Card> cards) {
    vector<int> values;
    for (auto card : cards) {
        values.push_back(card.value);
    }
    sort(values.begin(), values.end());

    return {1, values[4], values[3], values[2], values[1], values[0]};
}

/*
 * Combine all functions to score a holeCards.
 */
vector<int> CardUtil::scoreHand(vector<Card> cards) {
    vector<int> score;

    score = scoreStraightFlush(cards);
    if (!score.empty()) return score;

    score = scoreFourOfAKind(cards);
    if (!score.empty()) return score;

    score = scoreFullHouse(cards);
    if (!score.empty()) return score;

    score = scoreFlush(cards);
    if (!score.empty()) return score;

    score = scoreStraight(cards);
    if (!score.empty()) return score;

    score = scoreThreeOfAKind(cards);
    if (!score.empty()) return score;

    score = scoreTwoPairs(cards);
    if (!score.empty()) return score;

    score = scoreOnePair(cards);
    if (!score.empty()) return score;

    score = scoreHighCard(cards);
    return score;
}

bool CardUtil::compareScores(vector<int> score1, vector<int> score2) {
    for (int i=0; i<score1.size(); i++) {
        if (score1[i] > score2[i]) {
            return true;
        } else if (score1[i] < score2[i]) {
            return false;
        }
    }
    return false;
}

/*
 * Gets the best score given 5 community cards and two hole cards
 */
vector<int> CardUtil::findBestScore(vector<Card> communityCards, vector<Card> holeCards) {
    vector<Card> allCards = communityCards;
    allCards.insert(allCards.end(), holeCards.begin(), holeCards.end());

    vector<vector<int>> scores;
    vector<Card> hand;

    for (int i=0; i<allCards.size()-1; i++) {
        for (int j=i+1; j<allCards.size(); j++) {
            hand = allCards;
            hand.erase(hand.begin()+i);
            hand.erase(hand.begin()+j-1);
            scores.push_back(scoreHand(hand));
        }
    }

    vector<int> bestScore = {0};

    for (vector<int> score : scores) {
        if (compareScores(score, bestScore)) {
            bestScore = score;
        }
    }
    return bestScore;
}

/*
 * Get the best hand given 5 community cards and two hole cards
 */
vector<Card> CardUtil::findBestHand(vector<Card> communityCards, vector<Card> holeCards) {
    vector<Card> allCards = communityCards;
    allCards.insert(allCards.end(), holeCards.begin(), holeCards.end());

    vector<vector<Card>> allHands;
    vector<Card> hand;

    // Get all 5 hand permutations out of the 7 cards
    for (int i=0; i<allCards.size()-1; i++) {
        for (int j=i+1; j<allCards.size(); j++) {
            hand = allCards;
            hand.erase(hand.begin()+i);
            hand.erase(hand.begin()+j-1);
            allHands.push_back(hand);
        }
    }

    vector<int> bestScore = findBestScore(communityCards, holeCards);

    for (vector<Card> hand : allHands) {
        if (scoreHand(hand) == bestScore) {
            return hand;
        }
    }
}

/*
 * Translates numerical value of hand (1-9) to the actual name of the hand
 */
string CardUtil::deduceHandType(vector<int> score) {
    switch (score[0]) {
        case 1:
            return "high card";
        case 2:
            return "one pair";
        case 3:
            return "two pair";
        case 4:
            return "three of a kind";
        case 5:
            return "straight";
        case 6:
            return "flush";
        case 7:
            return "full house";
        case 8:
            return "four of a kind";
        case 9:
            return "straight flush";
    }
}