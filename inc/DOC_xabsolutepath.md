# MINISHELL

---

## 0_system

---

### **xabsolute_path**

```c
t_status xabsolute_path(char *dstpath, char *srcpath, char *envpathes, int mode);
```

---

### **概要**

`xabsolute_path` は、指定されたパスの絶対パスを取得し、その有効性を確認する関数です。  
結果のパスは **`dstpath`** にコピーされます。

---

### **引数**

| **引数**     | **型**                   | **説明**                          |
|--------------|-------------------------|----------------------------------|
| `dstpath`    | `char[MAX_PATH]`        | 絶対パスを格納するためのバッファ   |
| `srcpath`    | `char *`                | 解析（lexer）で取得したパス        |
| `envpathes`  | `char *`                | 環境変数 `$PATH`（`;` 区切り）     |
| `mode`       | `int`                   | `access` に渡すモード（`X_OK`, `F_OK`） |

---

### **戻り値**

`access(dstpath, mode)` の結果をそのまま返します。  
- **0**: 成功  
- **-1**: 失敗（パスが無効またはアクセス不可）  

---

### **動作の詳細**

1. **絶対パスの取得**  
   - `srcpath` が `/` で始まる場合は、そのまま **`dstpath`** にコピーします。  
   - それ以外の場合は、`envpathes` から候補パスを探索し、最初に有効なパスを **`dstpath`** にコピーします。

2. **有効性の確認**  
   - `access(dstpath, mode)` を用いて、パスの有効性（存在・実行可能性など）を確認します。

---

### **補足**

- **優先対応**  
  - `srcpath` が `/` で始まる場合は、即座に処理します。  

- **追加対応（余裕があれば）**  
  - `.` や `..` への対応  
  - 組み込みコマンド `cd ""` や `cd -` の処理（これは `builtin` 実装側に移行予定）  

---

### **使用例**

```c
char dstpath[MAX_PATH];
char *srcpath = "./a.out";
char *envpathes = "/usr/bin;/bin;/usr/local/bin";
int mode = X_OK;

if (xabsolute_path(dstpath, srcpath, envpathes, mode) == 0) 
{
    printf("Path found: %s\n", dstpath);
} else 
{
    printf("Path invalid or not executable\n");
}
```

---

### **注意事項**

- **`envpathes` の区切り**  
  環境変数 `$PATH` のディレクトリは `;`（セミコロン）で区切られている前提です。  

- **パスのバッファサイズ**  
  `dstpath` のサイズは **`MAX_PATH`**（定義済み）に収まる必要があります。

--- 