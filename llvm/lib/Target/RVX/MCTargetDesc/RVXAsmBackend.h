#ifndef LLVM_LIB_TARGET_RVX_MCTARGETDESC_RVXASMBACKEND_H
#define LLVM_LIB_TARGET_RVX_MCTARGETDESC_RVXASMBACKEND_H

#include "RVXFixupKinds.h"             
#include "llvm/MC/MCAsmBackend.h"      
#include "llvm/MC/MCFixupKindInfo.h"   
#include "llvm/MC/MCSubtargetInfo.h"   
#include "llvm/MC/MCTargetOptions.h"   
#include <cstdint>
#include <llvm-14/llvm/ADT/ArrayRef.h>
#include <llvm-14/llvm/MC/MCFixup.h>
#include <llvm-14/llvm/MC/MCInst.h>


namespace  llvm{

class MCAssembler; 
class MCObjectTargetWriter;
class MCRegisterInfo; 
class raw_ostream

class RVXAsmBackend : public MCAsmBackend{

    const MCSubtargetInfo &STI; 

    const MCTargetOptions &TargetOptions; 

public:

    RVXAsmBackend(const MCSubtargetInfo &STI, const MCTargetOptions &Options); 
    ~RVXAsmBackend() override = default;

    void applyFixup(const MCAssembler &Asm, const MCFixup &Fixup, 
                    const MCValue &Target, MutableArrayRef<char> Data,
                    uint64_t Value, bool IsResolved, 
                    const MCSubtargetInfo *STI) const override; 
    
    const MCFixupKindInfo &getFixupKindInfo(MCFixupKind Kind) const override; 

    unsigned getNumFixupKinds() const override{
        return RVX::NumTargetFixupKinds;
    }

    bool mayNeedRelaxation(const MCInst &Inst, 
                           const MCSubtargetInfo &STI) const override; 

    void relaxInstruction(MCInst &Inst, 
                          const MCSubtargetInfo &STI) const override; 

    bool shouldForceRelocation(const MCAssembler &Asm, const MCFixup &Fixup,
                             const MCValue &Target,
                             const MCSubtargetInfo *STI) override;


    bool writeNopData(raw_ostream &OS, uint64_t Count,
                    const MCSubtargetInfo *STI) const override;
    
    std::unique_ptr<MCObjectTargetWriter>
    createObjectTargetWriter() const override;
}
}

#endif 
