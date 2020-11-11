// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct BullCowCount
{
	int32 Bulls;
	int32 Cows;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void InitGame();
	void EndGame();
	void ProcessGuess(const FString& PlayerGuess);
	static bool IsIsogram(const FString& WordToCheck);
	//TArray<FString> GetValidWords(const TArray<FString>&) const;
	BullCowCount GetBullsCows(const FString& PlayerGuess) const;
	void PrintWordList(const TArray<FString>&) const;

	// Your declarations go below!
	private:
	FString CodeWord;
	int32 PlayerLives;
	bool GameOver;
	TArray<FString> Isograms;
};
