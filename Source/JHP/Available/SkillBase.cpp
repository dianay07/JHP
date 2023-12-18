#include "SkillBase.h"

USkillBase::USkillBase(const FObjectInitializer& ObjectInitializer)
{

}

void USkillBase::BeginPlay(ACharacter* InOwner, UActionData* InData)
{
	DrawAnimation = InData->DrawAnimation;
	AttackAnimations = InData->AttackAnimations;
	HitAnimations = InData->HitAnimations;
}