#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

extern char *build_file_name;
extern int yylineno;
int error_count = 0;

class Node
{
protected:
    vector<Node *> children;
    int lineno;

public:
    Node()
    {
        lineno = yylineno;
    }
    int getLineNo()
    {
        return lineno;
    }
    virtual string getType()
    {
        return " ";
    }
    virtual string toStr()
    {
        return "stmts";
    }
    void append(Node *n)
    {
        children.push_back(n);
    }
    vector<Node *> &getChildren()
    {
        return children;
    }
};

class Program : public Node
{
public:
    virtual string toStr()
    {
        return "Program";
    }
};

class Inteiro : public Node
{
protected:
    int value;

public:
    Inteiro(const int v)
    {
        value = v;
    }
    virtual string getType() override
    {
        return "inteiro";
    }

    virtual string toStr() override
    {
        return to_string(value);
    }
};

class Pf : public Node
{
protected:
    float value;

public:
    Pf(const float v)
    {
        value = v;
    }
    virtual string getType() override
    {
        return "Ponto Flutuante";
    }
    virtual string toStr() override
    {
        return to_string(value);
    }
};

class Boleano : public Node
{
protected:
    bool value;

public:
    Boleano(const bool v)
    {
        value = v;
    }
    virtual string getType() override
    {
        return "Boleano";
    }
    virtual string toStr() override
    {
        if (value)
        {
            return "Verdadeiro";
        }
        else
        {
            return "Falso";
        }
    }
};

class Palavra : public Node
{
protected:
    string frase;

public:
    Palavra(const string v)
    {
        frase = v;
    }
    virtual string getType() override
    {
        return "Palavra";
    }
    virtual string toStr() override
    {
        return frase;
    }
};

class Loop : public Node
{
protected:
    Node *value;

public:
    Loop(Node *v)
    {
        value = v;
        children.push_back(v);
    }

    virtual string toStr() override
    {
        return "Loop";
    }
};

class Enquanto : public Node
{
protected:
    Node *condition;
    Node *content;

public:
    Enquanto(Node *c, Node *n)
    {
        content = n;
        condition = c;
        children.push_back(c);
        children.push_back(n);
    }
    virtual Node *getCondition()
    {
        return condition;
    }

    virtual string toStr() override
    {
        return "Enquanto";
    }
};

class Se : public Node
{
protected:
    Node *condition;
    Node *content;

public:
    Se(Node *c, Node *n)
    {
        condition = c;
        content = n;
        children.push_back(c);
        children.push_back(n);
    }

    virtual Node *getCondition() { return condition; }

    virtual string toStr() override
    {
        return "Se";
    }
};

class SeSenao : public Node
{
protected:
    Node *contentSe;
    Node *contentSenao;
    Node *condition;

public:
    SeSenao(Node *c, Node *s, Node *sn)
    {
        condition = c;
        contentSe = s;
        contentSenao = sn;
        children.push_back(c);
        children.push_back(s);
        children.push_back(sn);
    }

    virtual Node *getCondition()
    {
        return condition;
    }
    virtual string toStr() override
    {
        return "Se Senão";
    }
};

class Id : public Node
{
protected:
    string name;

public:
    Id(const string n)
    {
        name = n;
    }

    virtual string getName()
    {
        return name;
    }

    virtual string getType()
    {
        return "Identificador";
    }

    virtual string toStr() override
    {
        return name;
    }
};

class Variavel : public Node
{
protected:
    string name;
    Node *value;

public:
    Variavel(const string n, Node *v)
    {
        name = n;
        value = v;
        children.push_back(v);
    }

    virtual Node *getNode()
    {
        return value;
    }

    virtual string getName()
    {
        return name;
    }

    virtual string toStr() override
    {
        return name + " =";
    }
};

class Unario : public Node
{
protected:
    Node *value;
    char operation;

public:
    Unario(char op, Node *v)
    {
        value = v;
        operation = op;
        children.push_back(v);
    }

    virtual string toStr() override
    {
        string aux;
        aux.push_back(operation);
        return aux;
    }
};

class OpBinaria : public Node
{
protected:
    Node *value1;
    Node *value2;
    string operation;

public:
    OpBinaria(Node *v1, char op, Node *v2)
    {
        value1 = v1;
        value2 = v2;
        operation = op;
        children.push_back(v1);
        children.push_back(v2);
    }

    virtual Node *getNode1() { return value1; }

    virtual Node *getNode2() { return value2; }

    virtual string toStr() override
    {
        return operation;
    }
};

class Mostra : public Node
{
protected:
    Node *value;

public:
    Mostra(Node *v)
    {
        value = v;
        children.push_back(v);
    }

    virtual string toStr()
    {
        return "mostra";
    }
};

void printf_tree_recursive(Node *noh)
{
    for (Node *c : noh->getChildren())
    {
        printf_tree_recursive(c);
    }
    cout << "N" << (long int)noh << "[label=\"" << noh->toStr() << "\"];" << endl;

    // imprime as ligações c/ os filhos
    for (Node *c : noh->getChildren())
    {
        cout << "N" << (long int)noh << "--" << "N" << (long int)c << ";" << endl;
    }
}

void printf_tree(Node *root)
{
    cout << "graph {" << endl;
    printf_tree_recursive(root);
    cout << "}" << endl;
}

class CheckVarDecl
{
private:
    set<string> symbolsInt, symbolsPf, symbolsBol, symbolsPal;

public:
    CheckVarDecl() {}

    /* Verificações Semanticas*/
    void check(Node *noh)
    {
        for (Node *c : noh->getChildren())
        {
            check(c);
        }
        /*verifica se existem nós do tipo Se, SeSenao ou Enquanto
        para direcionar o nó de condições dele para a verificação
        de condição
        */
        Se *se = dynamic_cast<Se *>(noh);
        if (se)
        {
            checkStringCondition(se->getCondition());
            return;
        }
        Enquanto *enquanto = dynamic_cast<Enquanto *>(noh);
        if (enquanto)
        {
            checkStringCondition(enquanto->getCondition());
            return;
        }

        SeSenao *senao = dynamic_cast<SeSenao *>(noh);
        if (senao)
        {
            checkStringCondition(senao->getCondition());
            return;
        }

        /*
        Verifica se os nós ID já foram
        atribuidos valores anteriormente
        */
        Id *id = dynamic_cast<Id *>(noh);
        if (id)
        {
            if (symbolsInt.count(id->getName()) <= 0 &&
                symbolsPf.count(id->getName()) <= 0 &&
                symbolsBol.count(id->getName()) <= 0 &&
                symbolsPal.count(id->getName()) <= 0)
            {
                error_count++;
                cout << build_file_name
                     << " "
                     << id->getLineNo()
                     << ":0: Erro Semântico: "
                     << id->getName()
                     << " Não definido!."
                     << endl;
            }
        }

        /*
        Se encontrara um nó do tipo Variavel, adiciona o nome
        da variavel em um conteiner do tipo set, representante
        a seu conjunto (Inteiros, Ponto Flutuante, Boleanos, Palavras)

        Porém se for encontrado uma expressão do tipo:
        a= falso + 10
        */
        Variavel *var = dynamic_cast<Variavel *>(noh);
        if (var)
        {
            Node *n = var->getNode();
            if (dynamic_cast<Inteiro *>(n))
            {
                symbolsInt.insert(var->getName());
                return;
            }
            if (dynamic_cast<Pf *>(n))
            {
                symbolsPf.insert(var->getName());
                return;
            }
            if (dynamic_cast<Palavra *>(n))
            {
                symbolsPal.insert(var->getName());
                return;
            }
            if (dynamic_cast<Boleano *>(n))
            {
                symbolsBol.insert(var->getName());
                return;
            }

            /*
            Verifica se é uma atribuição de uma váriavel já existente
            P.e.:
            ----------
            a=10;
            b=a;
            ----------
            Se a pertence a classe das váriaveis do tipo Inteiro
            Portanto b também pertence a classe de váriaveis do tipo Inteiro
            */
            Id *id = dynamic_cast<Id *>(n);
            if (id)
            {
                if (symbolsInt.count(id->getName()) != 0)
                {
                    symbolsInt.insert(var->getName());
                    return;
                }
                if (symbolsPf.count(id->getName()) != 0)
                {
                    symbolsPf.insert(var->getName());
                    return;
                }
                if (symbolsPal.count(id->getName()) != 0)
                {
                    symbolsPal.insert(var->getName());
                    return;
                }
                if (symbolsBol.count(id->getName()) != 0)
                {
                    symbolsBol.insert(var->getName());
                    return;
                }
            }

             /*
            Caso a atribuição seja de uma expressão, pega o verifica 
            o tipo do primeiro elemento da expressão
            P.e:
            ----------
            a=-10;
            b="asv";
            c=b+a
            se(c){ mostra a; }
            -------
            Portanto c será percentente a mesma classe do b, logo c é 
            percentence a classe Palavra, portanto C não irá entrar na 
            estrutura condicional 'Se'
            */

            OpBinaria *aux,*opb = dynamic_cast<OpBinaria *>(n);
            while (opb != NULL)
            {
                aux=opb;
                opb = dynamic_cast<OpBinaria *>(opb->getNode1());
            }

            Node *n1 = aux->getNode1();
            if (dynamic_cast<Inteiro *>(n1))
            {
                symbolsInt.insert(var->getName());
                return;
            }
            if (dynamic_cast<Pf *>(n1))
            {
                symbolsPf.insert(var->getName());
                return;
            }
            if (dynamic_cast<Palavra *>(n1))
            {
                symbolsPal.insert(var->getName());
                return;
            }
            if (dynamic_cast<Boleano *>(n1))
            {
                symbolsBol.insert(var->getName());
                return;
            }

            id = dynamic_cast<Id *>(n1);
            if (id)
            {
                if (symbolsInt.count(id->getName()) != 0)
                {
                    symbolsInt.insert(var->getName());
                    return;
                }
                if (symbolsPf.count(id->getName()) != 0)
                {
                    symbolsPf.insert(var->getName());
                    return;
                }
                if (symbolsPal.count(id->getName()) != 0)
                {
                    symbolsPal.insert(var->getName());
                    return;
                }
                if (symbolsBol.count(id->getName()) != 0)
                {
                    symbolsBol.insert(var->getName());
                    return;
                }
            }
        }
    }

    void checkStringCondition(Node *noh)
    {
        /*verifica se existe apenas
        string na condição das
        estruturas,Enquanto, Se, SeSenão*/

        Id *id = dynamic_cast<Id *>(noh);
        if (id)
        {
            if (symbolsPal.count(id->getName()) == 1)
            {
                error_count++;
                cout << build_file_name
                     << " "
                     << id->getLineNo()
                     << ":0: Erro semântico: "
                     << "Não use apenas uma variável do tipo [Palavra] em uma Condição"
                     << endl;

                return;
            }
        }

        Palavra *p = dynamic_cast<Palavra *>(noh);
        if (p)
        {
            error_count++;
            cout << build_file_name
                 << " "
                 << p->getLineNo()
                 << ":0: Erro semântico: "
                 << "Não use apenas uma variável do tipo [Palavra] em uma Condição"
                 << endl;
            return;
        }
    }

    // void checkUnary(Node *noh){

    // }
};

// verifica se está acontecendo operações binárias entre tipos diferentes de dados
class CheckTypeBinaryOp
{
private:
    set<string> symbols_inteiro, symbols_pf, symbols_palavra, symbols_boleano, symbols_id;

public:
    CheckTypeBinaryOp() {}

    void check(Node *noh)
    {
        for (Node *c : noh->getChildren())
        {
            check(c);
        }
        Variavel *var = dynamic_cast<Variavel *>(noh);
        if (var)
        {
            Inteiro *i = dynamic_cast<Inteiro *>(var->getNode());
            if (i)
            {
                symbols_inteiro.insert(var->getName());
            }

            Pf *pf = dynamic_cast<Pf *>(var->getNode());
            if (pf)
            {
                symbols_pf.insert(var->getName());
            }

            Palavra *p = dynamic_cast<Palavra *>(var->getNode());
            if (p)
            {
                symbols_palavra.insert(var->getName());
            }

            Boleano *b = dynamic_cast<Boleano *>(var->getNode());
            if (b)
            {
                symbols_boleano.insert(var->getName());
            }

            Id *id = dynamic_cast<Id *>(var->getNode());
            if (id)
            {
                symbols_id.insert(var->getName());
            }
            return;
        }

        OpBinaria *opb = dynamic_cast<OpBinaria *>(noh);
        if (opb)
        {
            Node *op1 = opb->getNode1();
            Node *op2 = opb->getNode2();

            Id *id1 = dynamic_cast<Id *>(op1);
            Id *id2 = dynamic_cast<Id *>(op2);
            if (id1 && id2)
            {
                return;
            }

            Inteiro *i1 = dynamic_cast<Inteiro *>(op1);
            Inteiro *i2 = dynamic_cast<Inteiro *>(op2);
            if (i1 && i2)
            {
                return;
            }

            Pf *pf1 = dynamic_cast<Pf *>(op1);
            Pf *pf2 = dynamic_cast<Pf *>(op2);
            if (pf1 && pf2)
            {
                return;
            }

            Boleano *b1 = dynamic_cast<Boleano *>(op1);
            Boleano *b2 = dynamic_cast<Boleano *>(op2);
            if (b1 && b2)
            {
                return;
            }

            Palavra *p1 = dynamic_cast<Palavra *>(op1);
            Palavra *p2 = dynamic_cast<Palavra *>(op2);
            if (p1 && p2)
            {
                return;
            }

            error_count++;
            cout << build_file_name
                 << " "
                 << opb->getLineNo()
                 << ":0: Semantic error: Operação entre ["
                 << opb->getNode1()->getType()
                 << "] e ["
                 << opb->getNode2()->getType()
                 << "] é inválido!\n"
                 << endl;
        }
    }
};
