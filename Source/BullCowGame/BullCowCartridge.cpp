// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    //FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    FFileHelper::LoadFileToStringArrayWithPredicate(Isograms, *WordListPath, 
        [](const FString& Word)
        {
            return Word.Len() < 8 && Word.Len() > 4 && IsIsogram(Word); 
        });
    InitGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if(GameOver)
    {
        InitGame();
        return;
    }
    //PrintLine("hidden word is " + CodeWord);

    ProcessGuess(Input);
}


void UBullCowCartridge::InitGame()
{
    
    PlayerLives = {5};
    GameOver = {false};

    if(Isograms.Num()>0)
    CodeWord = Isograms[FMath::RandRange(0, Isograms.Num()-1)]; //{TEXT("fuck")};
    else
    CodeWord = FString(TEXT("fuck"));

    ClearScreen();
    PrintLine(TEXT("Word List legth %d"), Isograms.Num());
    PrintLine(TEXT("Hello Shmeckle. This is a Bull Cows game"));
    PrintLine(TEXT("Guess a %d letter isogram to win the game"), CodeWord.Len() );
    PrintLine(TEXT("The hidden word is \'%s\'"), *CodeWord);
    PrintLine(TEXT("You have %d lives"), PlayerLives);
    PrintLine(TEXT("Enter your Schmeckle..."));
    
}


void UBullCowCartridge::EndGame()
{
    GameOver = {true};
    //ClearScreen();
    
    PrintLine(TEXT("Game Over! The hidden word was \'%s\'"), *CodeWord);
    PrintLine(TEXT("Press Enter to continue...."));
}

void UBullCowCartridge::ProcessGuess(const FString& PlayerGuess)
{
    ClearScreen();
    
    if(CodeWord == PlayerGuess)
    {
        PrintLine(TEXT("You win!\nPress enter to continue..."));
        GameOver = {true};
        return;
    }

    if(PlayerGuess.Len() != CodeWord.Len())
    {
        PrintLine( TEXT("Your guess has wrong number of letters\nHidden word is length %d\n Try again."), CodeWord.Len() );
        return;
    }

    if(!IsIsogram(PlayerGuess))
    {
        PrintLine(TEXT("Your guess is not an isogram! Try again"));
        return;
    }

    

    //PrintLine(TEXT("Hidden Word has lenght " + FString{"amew"} ) );
    if(PlayerLives>0)
    {
        PlayerLives--;
    }
    PrintLine(TEXT("Your schmeckle is smaller than mine"));
    ///PrintLine( TEXT("Hidden word is length %d"), CodeWord.Len() );
    PrintLine( TEXT("You have %d schmeckles left"), PlayerLives );
    
    
    if(PlayerLives <= 0)
    {
        EndGame();
        return;
    }
    BullCowCount Count = GetBullsCows(PlayerGuess);
    PrintLine(TEXT("You got %d bulls and %d cows"), Count.Bulls, Count.Cows );
    PrintLine(TEXT("Guess again!"));
    
}

bool UBullCowCartridge::IsIsogram(const FString& WordToCheck)
{
    if(WordToCheck.Len() <= 0)
        return false;
    
    for(int32 i = 0; i<WordToCheck.Len(); i++)
    {
        for(int32 j = i+1; j < WordToCheck.Len(); j++)
        {
            if(WordToCheck[i] == WordToCheck[j])
            {
                return false;
            }
        }
    }
    return true;
}

BullCowCount UBullCowCartridge::GetBullsCows(const FString& PlayerGuess) const
{
    BullCowCount NumBullsCows{0,0};
    if(PlayerGuess.Len() <= 0 || PlayerGuess.Len() != CodeWord.Len())
        return NumBullsCows;

    for(int32 i = 0; i<PlayerGuess.Len(); i++)
    {
        if(PlayerGuess[i] == CodeWord[i])
        {
            NumBullsCows.Bulls++;
            continue;
        }
        for(int32 j = 0; j<CodeWord.Len(); j++)
        {
            if(PlayerGuess[i] == CodeWord[j])
            {
                NumBullsCows.Cows++;
                break;
            }
        }
    }

    return NumBullsCows;
}