#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSItemSpawnVolume.generated.h"

UCLASS()
class RISEOFSUN_API ARSItemSpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	ARSItemSpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	class UBoxComponent* SpawningBox;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	FVector GetRandomPointInVolume() const;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnItem(TSubclassOf<AActor> ItemClass);
};