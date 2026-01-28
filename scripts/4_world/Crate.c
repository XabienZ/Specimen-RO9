class Crate extends Container_Base
{
    override bool CanPutInCargo(EntityAI parent)
    {
        return false;
    }

    override bool CanReceiveItemIntoCargo(EntityAI item)
    {
        return false;
    }

    override bool CanPutIntoHands(EntityAI parent)
    {
        return false;
    }
};