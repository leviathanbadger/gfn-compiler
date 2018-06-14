#include "pch.h"
#include "Eval/EvalContext.h"
#include "Eval/EvalMacros.h"
#include "Emit/MethodBuilder.h"
#include "Emit/OpNop.h"
#include "Emit/OpBrTrue.h"

TEST(OpBrTrue_eval, Simple_True) {
    Emit::MethodBuilder mb;
    auto tag = mb.createAnonymousTag();
    mb.addTagToNextOpcode(tag);
    mb.addOpcode(new Emit::OpNop());
    auto op = new Emit::OpBrTrue(tag);
    mb.addOpcode(op);

    mb.finalize();
    auto &ops = mb.ops();

    Eval::EvalContext ctx(ops);
    ctx.nextInstructionIndex() = (uint32_t)ops.size();
    pushAllToStack(ctx.stack(), 1);

    op->eval(ctx);

    EXPECT_TRUE(ctx.nextInstructionIndex() == 0);
    EXPECT_TRUE(ctx.stack().size() == 0);
}

TEST(OpBrTrue_eval, Simple_False) {
    Emit::MethodBuilder mb;
    auto tag = mb.createAnonymousTag();
    mb.addTagToNextOpcode(tag);
    mb.addOpcode(new Emit::OpNop());
    auto op = new Emit::OpBrTrue(tag);
    mb.addOpcode(op);

    mb.finalize();
    auto &ops = mb.ops();

    Eval::EvalContext ctx(ops);
    ctx.nextInstructionIndex() = (uint32_t)ops.size();
    pushAllToStack(ctx.stack(), 0);

    op->eval(ctx);

    EXPECT_TRUE(ctx.nextInstructionIndex() == ops.size());
    EXPECT_TRUE(ctx.stack().size() == 0);
}

TEST(OpBrTrue_eval, InvalidTag) {
    Emit::MethodBuilder mb;
    auto tag = mb.createAnonymousTag();
    mb.addOpcode(new Emit::OpNop());
    auto op = new Emit::OpBrTrue(tag);
    mb.addOpcode(op);

    mb.finalize();
    auto &ops = mb.ops();

    Eval::EvalContext ctx(ops);
    ctx.nextInstructionIndex() = (uint32_t)ops.size();
    pushAllToStack(ctx.stack(), 1);

    EXPECT_THROW(op->eval(ctx), std::logic_error);
}

TEST(OpBrTrue_eval, InvalidStack) {
    Emit::MethodBuilder mb;
    auto tag = mb.createAnonymousTag();
    mb.addTagToNextOpcode(tag);
    mb.addOpcode(new Emit::OpNop());
    auto op = new Emit::OpBrTrue(tag);
    mb.addOpcode(op);

    mb.finalize();
    auto &ops = mb.ops();

    Eval::EvalContext ctx(ops);
    ctx.nextInstructionIndex() = (uint32_t)ops.size();

    EXPECT_THROW(op->eval(ctx), std::logic_error);
}
