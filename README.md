# Compiladores
Materia de Compiladores durante a faculdade de Ciência da Computação

## Para rodar
1. Entrar na pasta  `scr/`

2. Executar `./Compilador  [Nome do arquivo] [Opções]`

    > Opções
    >
    >> `d` - mostrar toda a construção da árvore passo a passo 
    >     
    >> `-f` - forçar o print da árvore

## Verificações semanticas contidas
> ### 1. Verificação de váriavel declarada
>   
>   * Verifica se toda váriavel existente possuem algum tipo já declarado.
>> Por exemplo:   
>>`a= 10*10;`  
>>`mostra b;`
>>>### retorno:    
>>>`erro4 14:0: Erro Semântico: b Não definido`
>
> ### 2. Verificação se as condições de estruturas contém apenas String.
>   
>   * Verifica se as condições das estruturas `Se`, `Se-senão` e `Enquanto` possuem apenas `String` na sua estrutura de condição.
>> Por exemplo:  
>>`a= "abc;`  
>>`se(a){mostra a;}`
>>>### retorno:    
>>>`Erro semântico: Não use apenas uma variável do tipo [Palavra] em uma Condição`
>
> ### 3. 
.  
.  
.  

TODO




<!-- <span style="color:red">some text</span> -->