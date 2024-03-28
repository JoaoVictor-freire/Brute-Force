# Brute-Force

### Enunciado 

Você trabalha em uma empresa em que existem 10 arquivos de senhas 
criptografadas que precisam ser recuperadas. O algoritmo que descriptografa as 
senhas foi perdido, restando apenas o código que realiza a codificação das 
senhas:

________________________________________________________________________________




________________________________________________________________________________

Suponha que não seja possível fazer a engenharia reversa do código e que você 
deva recuperar as senhas contidas nos 10 arquivos utilizando "força bruta"; 
faça então um programa em C que utilize processos para realizar as tentativas
em concorrência. As senhas tem 4 caracteres e são compostas apenas por letras
maiúsculas. Seu código então deverá gerar todas strings de 4 caracteres para
cada entrada do arquivo de senhas e testar se a versão criptografada da palavra
gerada é igual a palavra criptografada no arquivo - em caso positivo, a senha 
foi quebrada.
