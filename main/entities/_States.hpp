#pragma once
class States {
    public:

    States();
    
    bool isMoving;
    bool isAttacking;
    bool isTakingDmg;
    bool isDead;

    bool isProjectile;
    bool hatesPlayer;

};

States::States() {
    isMoving=false;
    isAttacking=false;
    isTakingDmg=false;
    isDead=false;

    isProjectile=false;
    hatesPlayer=true;
}