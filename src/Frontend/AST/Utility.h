#pragma once

#include "Expression.h"
#include <Backend/CodeGen/IR/IRContext.h>
#include <Backend/CodeGen/IR/Constant.h>
#include <Backend/CodeGen/IR/Operators/Assign.h>
#include <Backend/CodeGen/IR/Types/DTNull.h>

#include "Variable.h"
#include "String.h"
#include <Frontend/AST/Number.h>
#include "Index.h"

#include <vector>
#include <memory>

namespace Frontend::AST
{
    static std::unique_ptr<Expression> SyntaxToExpression(std::vector<std::pair<std::string, std::string>> syntax, std::shared_ptr<Backend::CodeGen::IR::IRContext> con)
    {
        std::unique_ptr<Expression> expr;
        if (syntax.size() == 1)
        {
            if (syntax[0].first.compare("id") == 0)
            {
                // Variable
                std::shared_ptr<Backend::CodeGen::IR::Variable> v = con->GetLocalVariable(syntax[0].second);
                if (!v)
                {
                    std::string str = "ERROR: Unexpected variable: " + syntax[0].second + "!\n";
                    printf(str.c_str());
                    exit(1);
                }

                std::unique_ptr<Frontend::AST::Variable> var(new Frontend::AST::Variable(syntax[0].second));
                var->SetType(v->GetType());

                expr = std::move(var);
            }
            else if (syntax[0].first.compare("num") == 0)
            {
                std::unique_ptr<Number> num(new Number(syntax[0].second));
                expr = std::move(num);
            }
            else if (syntax[0].first.compare("str") == 0)
            {
                // String
                std::unique_ptr<String> str(new String(syntax[0].second));
                expr = std::move(str);
            }
        }
        else if (syntax.size() == 2)
        {
            if (syntax[0].first.compare("id") == 0)
            {
                if (syntax[1].first.compare("index") == 0)
                {
                    std::unique_ptr<Index> index(new Index(syntax[0].second, syntax[1].second));
                    expr = std::move(index);
                }
                else if (syntax[1].first.compare("type") == 0)
                {
                    // Variable
                    std::unique_ptr<Frontend::AST::Variable> var(new Frontend::AST::Variable(syntax[0].second, syntax[1].second));

                    expr = std::move(var);
                }
            }
        }
        else if (syntax.size() == 3)
        {
            if (syntax[0].first.compare("id") == 0 && syntax[1].first.compare("ptr") == 0 && syntax[2].first.compare("type") == 0)
            {
                // Variable
                std::unique_ptr<Frontend::AST::Variable> var(new Frontend::AST::Variable(syntax[0].second, syntax[2].second, syntax[1].second));
                expr = std::move(var);
            }
        }
        else
        {
            printf("ERROR: Unexpected error in SyntaxToExpression");
            exit(1);
        }

        return std::move(expr);
    }
}