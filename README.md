# **TaCTi**  
**Grupo: Maremoto**  

## **Antes de Jugar**  

### **1) Instalar y Configurar cURL**  
El juego requiere la biblioteca **cURL** para funcionar correctamente.  

#### **Windows**  
- Descargar cURL desde [aquí](https://curl.se/windows/).  
- Descomprimir el archivo ZIP en una carpeta que no vayan a eliminar.  
- Agregar la ruta de la carpeta `bin` dentro de la variable de entorno **PATH**.  

#### **Configuración en Code::Blocks**  
- **Settings > Compiler > Linker Settings**  
  - Agregar la ubicación de `lib\libcurl.a`.  
  - En **Other linker options**, agregar:  
    ```
    -lcurl
    -lws2_32
    -lssl
    -lcrypto
    -lz
    ```  
- **Settings > Compiler > Search directories**  
  - **Compiler y Resource compiler:** Agregar la ubicación de `include`.  
  - **Linker:** Agregar la ubicación de `lib`.  

### **2) Configurar `configuracion.txt`**  
Antes de jugar, es necesario editar el archivo `configuracion.txt` y reemplazar los valores entre corchetes (`[...]`) por los valores deseados:  
```
[URL de tu API]|[CODIGO DE GRUPO]
[CANTIDAD DE PARTIDAS POR JUGADOR]
```  

### **3) Especificar el Archivo de Configuración en Code::Blocks**  
En **Project -> Set programs' arguments...**, agregar el nombre del archivo de configuración.  
Ejemplo:  
```
configuracion.txt
```  

---

## **¿Cómo Jugar?**  

Al iniciar el juego, aparecerá un menú con 3 opciones, que se seleccionan con el **cursor del mouse**:  
- **[A] Jugar**  
- **[B] Ver ranking del equipo**  
- **[C] Salir**  

### **[A] Jugar**  
1. Ingresar los nombres de los jugadores, separados por **Enter**. Para finalizar, escribir `"fin"`.  
2. Elegir la dificultad:  
   - **0** → Fácil  
   - **1** → Difícil  
3. Se mostrará el **orden de turnos** (determinado al azar) y se pedirá presionar **Enter**.  
4. Para cada jugador, antes de empezar su turno, deberá presionar **Enter** cuando esté listo.  
5. Comienza el juego contra la **IA**.  
   - Cada jugador tendrá un símbolo (`X` u `O`, asignado al azar).  
   - Siempre comienza la **X**.  
   - Para colocar una ficha, hacer clic en la casilla deseada.  
   - La IA jugará automáticamente después de cada turno del jugador.  
   - El juego continúa hasta que alguien gane o haya un empate.  
6. Se repite el proceso hasta completar el número de partidas configuradas.  
7. Al finalizar, se generará un archivo de informe con el formato:  
   ```
   informe-juego_AAAA-MM-DD-HH-MM.txt
   ```  
   Este archivo contendrá:  
   - Cómo quedó el tablero en cada partida.  
   - Los puntos obtenidos.  
   - El total por jugador.  
   - El puntaje más alto.  
8. Los resultados se enviarán automáticamente a la **API**.  

### **[B] Ver ranking del equipo**  
Muestra el **top de puntajes** del equipo.  

---
