# tareaCalceteam
### Como compilar y ejecutar (desde terminal git bash)
- Compilar con `$ gcc -g main.c list.c -o main`
- Correr con `$ ./main`
### Configuracion git
- Para que al subir cambios salga tu usuario y no salga "Your Name"
  ```
  $ git config --global user.name "nombre_usuario"
  $ git config --global user.email "mail@test.com"
  ```
### Funcionamiento de opciones
- Todas las funciones y opciones correspondientes al menú principal de la aplicación funcionan correctamente. El único error que se ha encontrado es al leer y escribir strings que contengan carácteres especiales del español como la letra ñ, este parece ser que es un problema de la interfaz de windows que por razones del idioma de configuración no admite como tal la lectura y escritura de los caracteres mencionados, esto se intentó solucionar importado librerías que podrían solucionar esto como locale.h y windows.h no se obtuvieron resultados positivos.

### Coevaluación
- Oscar Rojas:
- Benjamín Rojas:
- Ramiro Magnatera:
- Víctor Granda:

### Puntos de premio
- Oscar Rojas:
- Benjamín Rojas:
- Ramiro Magnatera:
- Víctor Granda:
