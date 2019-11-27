#pragma once

#include "Expression.h"
#include "../AsmContext.h"

#include "Variable.h"
#include "Number.h"
#include "String.h"
#include "Negative.h"
#include "Array.h"

namespace Backend::CodeGen::Asm::AST
{
    static std::unique_ptr<Expression> SyntaxToExpression(std::vector<std::pair<std::string, std::string>> syntax, Asm::AsmContext& context)
    {
        if (syntax.size() == 1)
        {
            if (syntax[0].first.compare("id") == 0)
            {
                Var v = context.GetVar(syntax[0].second);
                if (v.size == -1)
                {
                    _Array arr = context.GetArray(syntax[0].second);
                    if (arr.size == -1)
                    {
                        // Is it a member in type?
                        Type t = context.GetType(syntax[0].second);
                        if (t.size == -1)
                            return nullptr; // Fix in element

                        // It is
                        std::unique_ptr<AST::Variable> var(new AST::Variable(v.id, v.type, v.ptr, false));
                        var->SetOfffset(v.position);
                        return std::move(var);
                    }

                    std::unique_ptr<AST::Array> a(new AST::Array(arr.type, arr.id, std::to_string(arr.arraySize)));
                    return std::move(a);
                }

                std::unique_ptr<AST::Variable> var(new AST::Variable(v.id, v.type, v.ptr, false));
                var->SetOfffset(v.position);
                return std::move(var);
            }
            else if (syntax[0].first.compare("str") == 0)
            {
            }
        }
        else if (syntax.size() == 2)
        {
            if (syntax[0].first.compare("type") == 0)
            {
                if (syntax[1].first.compare("num") == 0)
                {
                    std::unique_ptr<AST::Number> num(new AST::Number(syntax[1].second));
                    return std::move(num);
                }
            }
            if (syntax[0].first.compare("lval") == 0)
            {
                if (syntax[1].first.compare("id") == 0)
                {
                    Var v = context.GetVar(syntax[1].second);
                    if (v.size == -1)
                    {
                        _Array arr = context.GetArray(syntax[1].second);
                        if (arr.size == -1)
                        {
                            std::string s = "ERROR: Unexpected identifier: " + syntax[1].second + "!\n";
                            printf(s.c_str());
                            exit(1);
                        }

                        std::unique_ptr<AST::Array> a(new AST::Array(arr.type, arr.id, std::to_string(arr.arraySize)));
                        return std::move(a);
                    }

                    std::unique_ptr<AST::Variable> var(new AST::Variable(v.id, v.type, false, true));
                    var->SetOfffset(v.position);
                    return std::move(var);
                }
            }
        }
        else if (syntax.size() == 3)
        {
            if (syntax[0].first.compare("type") == 0 && syntax[1].first.compare("ptr") == 0 && syntax[2].first.compare("id") == 0)
            {
                // Variable
                std::unique_ptr<Backend::CodeGen::Asm::AST::Variable> var(new Backend::CodeGen::Asm::AST::Variable(syntax[2].second, syntax[0].second, true, false));
                return std::move(var);
            }
            if (syntax[0].first.compare("type") == 0 && syntax[1].first.compare("ptr") == 0 && syntax[2].first.compare("str") == 0)
            {
                // String
                std::unique_ptr<AST::String> str(new AST::String(syntax[2].second));
                return std::move(str);
            }
            if (syntax[0].first.compare("type") == 0 && syntax[1].first.compare("minus") == 0 && syntax[2].first.compare("num") == 0)
            {
                std::unique_ptr<AST::Negative> negative(new AST::Negative(syntax[2].second));
                return std::move(negative);
            }
        }

        return nullptr;
    }

    static size_t TypeToSize(const std::string type)
    {
        if (type.compare("i8") == 0) return 1;
        if (type.compare("i16") == 0) return 2;
        if (type.compare("i32") == 0) return 4;
        if (type.compare("i64") == 0) return 8;
        return 0;
    }
}
