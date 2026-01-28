class Specimen_RO9 : ZombieMaleBase{};

modded class Specimen_RO9
{
    ref Timer m_BreathTimer;
    ref EffectSound m_BreathSound;

    void Specimen_RO9()
    {
        SetEventMask(EntityEvent.POSTFRAME);

        m_BreathTimer = new Timer(CALL_CATEGORY_GAMEPLAY);
        m_BreathTimer.Run(Math.RandomFloatInclusive(5, 10), this, "TryPlayBreathing", NULL, true);
    }

    void ~Specimen_RO9()
    {
        if (m_BreathTimer)
            m_BreathTimer.Stop();

        if (m_BreathSound)
            m_BreathSound.Stop();
    }

    void TryPlayBreathing()
    {
        if (!IsAlive())
            return;

        vector velocity = GetVelocity(this);
        if (velocity.Length() > 0.4) // moving → skip
            return;

        if (Math.RandomFloat01() > 0.6) // 40 % chance each tick
            PlayBreathing();
    }

    void PlayBreathing()
    {
        // stop any currently looping instance first
        if (m_BreathSound && m_BreathSound.IsSoundPlaying())
            m_BreathSound.Stop();

        if (GetGame().IsClient())
        {
            m_BreathSound = SEffectManager.PlaySoundOnObject("Subject_Breathing_Set", this);
        }
    }

    override void EOnPostFrame(IEntity other, int extra)
    {
        float scale = 1.3;
        vector transform[4];
        GetTransform(transform);

        transform[0] = transform[0] * scale;
        transform[1] = transform[1] * scale;
        transform[2] = transform[2] * scale;

        SetTransform(transform);
        Update();
    }

    override void EOnFrame(IEntity other, float timeSlice) // | EntityEvent.FRAME
    {
        vector rotation = GetYawPitchRoll();
        SetYawPitchRoll(Vector(rotation[0], 0, 0));
    }
    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);

        if (!GetGame().IsServer())
            return;

        if (GetType() == "Specimen_RO9")
        {
            vector pos = GetPosition();
            pos[1] = pos[1] + 0.0;

            EntityAI lootHolder = EntityAI.Cast(GetGame().CreateObject("Crate", pos));
            if (!lootHolder)
                return;

            lootHolder.GetInventory().CreateInInventory("Specimen_Head");

            // Start delete loop
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CheckAndDeleteLootHolder, 1000, true, lootHolder);
        }
    }

    void CheckAndDeleteLootHolder(EntityAI lootHolder)
    {
        if (!lootHolder)
            return;

        CargoBase cargo = lootHolder.GetInventory().GetCargo();
        if (!cargo)
            return;

        // Delete when empty
        if (cargo.GetItemCount() == 0)
        {
            GetGame().ObjectDelete(lootHolder);
        }
    }
}
