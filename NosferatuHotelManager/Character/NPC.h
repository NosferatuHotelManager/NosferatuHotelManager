#include "../stdafx.h"
#include "Character.h"
#include "../DecisionMaker.h"

class NPC : public Character {
	
	static std::vector<NPC> NPCStack;

	static NPC getNPCByID(int ID);
	static void createNPC(std::string type);

private:
	int characterID;

	char personType;
	int basePerceptiveness;
	int baseFriendliness;
	int baseSocialness;
	int baseAggressiveness;
	int suspicion;
	std::string age;
	bool isCharacterMale;

	std::map<int, int> friendlinessModifiers;

	std::vector<Activity> activitiesByPhaseOfDay[6];

	DecisionMaker decisionMaker;

public:
	NPC();

	char getPersonType();
	int getPerceptiveness();
	int getBaseFriendliness();
	int getBaseSocialness();
	int getAggressiveness();
	int getSuspicion();
	void setSuspicion(int newSuspicionLevel);
	std::string getAge();
	bool isMale();

	int getFriendlinessTowardsCharacter(int characterID);
	void setFriendlinessToCharacter(int characterID, int newFriendliness);

};

