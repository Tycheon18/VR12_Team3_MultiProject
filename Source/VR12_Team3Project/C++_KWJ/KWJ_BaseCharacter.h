// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponBaseClass.h"
#include "KWJ_BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeftGame);

UCLASS()
class VR12_TEAM3PROJECT_API AKWJ_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKWJ_BaseCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	bool bDisableGameplay = false; // Check to blueprint input compatible

	UFUNCTION(Server, Reliable)
	void ServerLeaveGame();

	FOnLeftGame OnLeftGame;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Building")
	class UBuildManagerComponent* BuildManager;

	UPROPERTY(ReplicatedUsing = OnRep_CurHp, VisibleAnywhere, BlueprintReadWrite, Category = "PlayerState")
	float CurHp = 100.f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void UpdateHUDHp();
	void UpdateHUDStamina();

	void PollInit();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* OverheadWidget;

	UPROPERTY(EditAnywhere,  Category = "PlayerState")
	float MaxHp = 100.f;



	UPROPERTY(EditAnywhere, Category = "PlayerState")
	float MaxStamina = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Stamina, VisibleAnywhere, Category = "PlayerState")
	float CurStamina = 100.f;

	UFUNCTION(BlueprintCallable)
	void OnRep_CurHp();

	UFUNCTION()
	void OnRep_Stamina();

	UPROPERTY(Replicated)
	class AWeaponBaseClass* Weapon;

	UPROPERTY()
	class AKWJ_PlayerController* PlayerController;

	class AKWJ_PlayerState* PlayerState;

	bool bLeftGame = false;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE float GetCurHp() const { return CurHp; }
	FORCEINLINE float GetMaxHp() const { return MaxHp; }
	FORCEINLINE float GetCurStamina() const { return CurStamina; }
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }
};
