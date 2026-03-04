#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/RSItemData.h"
#include "RSItemSpawnVolume.generated.h"

UCLASS()
class RISEOFSUN_API ARSItemSpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	ARSItemSpawnVolume();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnRandomItem();
	
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnItem(TSubclassOf<AActor> ItemClass);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	class UBoxComponent* SpawningBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	UDataTable* ItemDataTable;

	FVector GetRandomPointInVolume() const;
	FRSItemData* GetRandomItem()const;
	//void SpawnItem(TSubclassOf<AActor> ItemClass);

};