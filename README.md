# Sistema de Manutenção de Contas

## Descrição

Sistema desenvolvido em C para gerenciamento simples de contas utilizando arquivos binários.

Os dados dos clientes são armazenados no arquivo `clientes.dat` através de registros de tamanho fixo.

## Funcionalidades

* Cadastrar cliente em uma posição específica do arquivo.
* Consultar cliente pelo número da conta.
* Atualizar saldo de um cliente.
* Encerrar (remover) uma conta.
* Listar todos os clientes cadastrados.
* Reiniciar a leitura do arquivo utilizando `rewind()`.
* Encerrar o sistema.

## Tecnologias e Conceitos Utilizados

* Linguagem C
* Structs
* Arquivos binários
* `fwrite()`
* `fread()`
* `fseek()`
* `rewind()`
* Menu com `switch-case`

## Como Executar

### Compilar

```bash
gcc main.c -o sistema
```

### Executar

**Windows**

```bash
sistema.exe
```

**Linux / Mac**

```bash
./sistema
```

## Arquivo Gerado

Durante a execução será criado automaticamente o arquivo:

```text
clientes.dat
```

Este arquivo é responsável por armazenar os dados dos clientes cadastrados.
