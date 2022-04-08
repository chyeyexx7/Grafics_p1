# VisRayTrace 2021-22

## Equip:
**A02**
* [Chang Ye](https://github.com/chyeyexx7)
* [Sergi Lopez](https://github.com/sergiLopez)
* [Noel Vázquez](https://github.com/buildcrash)
* [Alejandro Couciero](https://github.com/Couci27)


### Features (marqueu les que heu fet i qui les ha fet)
- Fase 1
    - [x] Background amb degradat
      - Noel Vázquez
   
    - Creació de nous objectes i interseccions (VIRTUALWORLD) 
        - [x] 3.1.a. Mapping de mons virtuals
          - Noel Vázquez
        - [x] 3.1.b. Hit Triangle
          - Noel Vázquez
        - [x] 3.1.c. Hit Boundary Object
          - Chang Ye
        - [x] 3.1.d. Hit Cilindre
          - Chang Ye
    - Creació de REAL DATA
        - [x] 3.2.a. Transformacions Translació i Escalat amb gizmos esferes
          - Noel Vázquez
        - [x] 3.2.b. Pla de terra
          - Noel Vázquez
        - [x] 3.2.c. Gizmo de Triangle
          - Chang Ye
        - [x] 3.2.d. Gizmo de Cilindre
          - Chang Ye
        - [x] Noves dades
          - Chang Ye
       

- Fase 2
    - [x] Antialiasing
      - Chang Ye
    - [x] Gamma Correction
      - Chang Ye
    - [x] Blinn-Phong
      - Chang Ye
    - [x] Ombres amb objectes opacs
      - Chang Ye
    - [x] Reflexions
      - Chang Ye
    - [x] Transparències
      - Chang Ye
    - [x] Visualització amb dades reals
      - Chang Ye
    
    
- Fase 3
  - [x] Texture mapping en el pla
    - Chang Ye
  - [x] MaterialTextura
    - Chang Ye
  - [x] Nova escena de dades
    - Chang Ye
   
- Parts opcionals
  - [ ] Nous objectes paramètrics 
  - [ ] Penombres
   
  - [ ] Diferents tipus de llums 
    
  - [x] Multiple-scattering 
    - Chang Ye
   
  - [ ] Escena CSG 
  
  - [ ] Ambient occlusion
    
  - [ ] Defocus blur
   
  - [ ] Més d'una propietat en les dades reals
   
  - [ ] Animacions amb dades temporals
  
  - [ ] Ombres atenuades segons objectes transparents
  
  - [ ] Colors d'ombra segons els colors dels objectes transparents
  
  - [ ] Mapeig de les dades reals en una esfera
  
  - [ ] Ús de diferents paletes 
    
    
### Explicació de la pràctica    
  * **Organització de la pràctica**
  
En un principio habíamos pensado ir haciendo entre los cuatro componentes del grupo partes diferentes de las diferentes fases para poder ir avanzando cada semana. Debido a que durante el periodo de entrega, dos de los compañeros, Alejandro y Sergi, no han hecho nada, finalmente hemos realizado la práctica solo entre Chang y Noel. 

Las partes que ha hecho cada componente del grupo se puede ver en el apartado de feature, pero resumidamente; teníamos pensado en ir repartiendo las fases 2 y 3, pero debido a que habíamos perdido muchísimo tiempo en finalizar la fase 1 luego no pudimos avanzar la fase 2 ni 3. Además, a causa de los parciales y proyectos de otras asignaturas, Noel no ha tenido mucho tiempo disponible, por lo que la tarea de realizar las fotos e informe se ha encargado el Chang.
  
  * **Decisions a destacar**
  
  No se ha tomado ninguna dicisión importante en particular, simplemente hemos ido trabajando cada parte que se ha repartido entre los dos.
### Screenshots de cada fase

Respecto a los parámetros utilizado en las 3 fases de la práctica, hemos usado las configuraciones dado por el guión de la práctica, por lo que no hemos tomado apuntes de las configuraciones que hemos utilizado en los diferentes screenshots. Los archivos `.json` mencionado están dentro de la carpeta `resources`.

* **Fase 1**: 

closestHit del Triangulo utilizando los datos `triangles.json` y setup  `setupRenderTwoSpheres.json`:

![fase1Triangles](https://user-images.githubusercontent.com/72078368/162372718-c286327e-49a8-4ad8-a16f-1948002a160e.png)

closestHit del Mesh utilizando los datos `meshExample.json` y setup `setupRenderTwoSpheres.json`:

![fase1Mesh](https://user-images.githubusercontent.com/72078368/162373405-b356dd6a-15ae-4aea-bc86-1ec760be685a.png)

closestHit del Cilindro utilizado los datos `oneCylinder.json` y setup `setupRenderOneSphere.json`:

![fase1Cylinder](https://user-images.githubusercontent.com/72078368/162373513-d9b041a9-cbf0-4ff0-89ae-49391c17e334.png)

Real data utilizando un data10 nuevo que contiene un fittedPlane con esferas y cilindros utilizando los datos `data10Fase1.json` y setup `setupData10.json`. Debido a que las coordenadas que proporciona en el guión de la práctica, podemos observar que la base es muy pequeá y las figuras están fuera.

![fase1Data10](https://user-images.githubusercontent.com/72078368/162373837-f9985f3c-7b95-48a6-b0cf-864ba1dccb60.png)

* **Fase 2**: 

En esta cabe mencionar que la atenuación utilizada para los cálculos de Blinn-Phong es la que nos da del guión de la práctica: 0.5 + 0.01*d^2.

<ins>Apartado A</ins> 

En este apartado se han utilizado los datos `twoSpheres.json` y setup `setupRenderTwoSpheres.json`:

![fase2A1](https://user-images.githubusercontent.com/72078368/162374443-999ec3dc-4977-4120-ba78-fe469faa099f.png)

Añadiendo AAx10:

![fase2A2](https://user-images.githubusercontent.com/72078368/162375034-fc025223-c826-4915-8045-63e4754dc0ff.png)

Añadiendo Gamma Correction:

![fase2A3](https://user-images.githubusercontent.com/72078368/162375087-498c968e-dcb0-4d21-80ea-e2e0b95eb360.png)

<ins>Apartado B</ins>

En este apartado se han utilizado los datos `twoSpheres.json` y setup `setupRenderTwoSpheres.json`.

Calculando el color solo con la componente ambiente:

![fase2Ba](https://user-images.githubusercontent.com/72078368/162375257-424fb398-585f-4241-a607-ac443881f0fd.png)

Calculando el color solo com la componente difusa:

![fase2Bb](https://user-images.githubusercontent.com/72078368/162375342-bab9b288-44e2-4fd4-923e-3d90491cf003.png)

Calculando el color solo con la componente especular:

![fase2Bc](https://user-images.githubusercontent.com/72078368/162375365-af172ba5-8ed0-4586-b7b7-285dfb4ebf82.png)

Juntando las tres componentes:

![fase2Bd](https://user-images.githubusercontent.com/72078368/162375437-e77288b0-8719-478c-92c6-7d3e61bcaf1c.png)

Añadiendo atenuación con profundidad junto con las tres componentes:

![fase2Be](https://user-images.githubusercontent.com/72078368/162375546-5f3b9057-ff3e-4e39-adae-37c546973138.png)

Añadiendo ambiente global respecto la imágen anterior:

![fase2Bf](https://user-images.githubusercontent.com/72078368/162375617-f8ee126d-422b-4bc2-9b13-94e8a5951215.png)

Añadir sombra al método Blinn-Phong:

![fase2Bg](https://user-images.githubusercontent.com/72078368/162375674-044ebb62-a7bd-4576-82b2-0795c53ab6d2.png)

Ahora probamos los datos `spheresLambertianes.json` y setup `setupRenderSpheres.json`

![fase2Bh](https://user-images.githubusercontent.com/72078368/162375792-672b64c4-df53-4b5a-ad20-b59b9e35ef90.png)

Creando una escena más compleja que contiene 10 objetos:

![fase2Bi10figures](https://user-images.githubusercontent.com/72078368/162375848-18194d7c-88ae-4e2c-8f11-8f29b69ac6e3.png)

<ins>Apartado C</ins>

En este apartado se han utilizado los datos `twoSpheres.json` y setup `setupRenderTwoSpheres.json`.

Añadiendo recursión a `RayColor` teniendo en cuenta el color del background con MAXDEPTH = 1:

![fase2C2depth1](https://user-images.githubusercontent.com/72078368/162375968-4238dea2-30ea-4873-b8de-161a9d26869c.png)

Añadiendo recursión a `RayColor` teniendo en cuenta el color del background con MAXDEPTH = 10:

![fase2C2depth10](https://user-images.githubusercontent.com/72078368/162376096-f348eb0a-b0f3-4c3b-81f4-eafcfb0189a4.png)

Creando el nuevo material Metal y MAXDEPTH = 1: 

![fase2C4depth1](https://user-images.githubusercontent.com/72078368/162376352-0267098f-34dc-4f18-92c2-71f8170c5286.png)

Creando el material nuevo Metal y MAXDEPTH = 10: 

![fase2C4depth10](https://user-images.githubusercontent.com/72078368/162376374-da6d2f1e-b929-4b83-b2b8-9ae02b2c7ab5.png)

<ins>Apartado D</ins>

En este apartado se han utilizado los datos `twoSpheres.json` y setup `setupRenderTwoSpheres.json`. También se ha tenido en cuenta el background.

Creando el nuevo material Transparent y MAXDEPTH = 1:

![fase2D2depth1](https://user-images.githubusercontent.com/72078368/162376601-4f1bbea9-85e8-41c0-8a43-31911d3342b9.png)

Creando el nuevo material Transparent y MAXDEPTH = 4:

![fase2D2depth4](https://user-images.githubusercontent.com/72078368/162376713-5a652504-35b2-433f-8de3-0dfd01c56d7f.png)

Probando `meshExample.json` con setup `setupRenderTwoSpheres.json` para ver si funciona correctamente el Blinn-Phong con mesh:

![fase2D3depth4](https://user-images.githubusercontent.com/72078368/162377090-f56b31e7-7c08-4e53-b78f-19555843e9e6.png)

<ins>Apartado E</ins>

En este apartado todas las configuraciones son las que menciona en el guión de práctica.

Usando los datos `dadesBCN.json` y setup `setupDataBCN.json` truncando valor mínimo a 0.1 y multiplicando máximo virtual y por 0.7:

![fase2EdadesBCN](https://user-images.githubusercontent.com/72078368/162376930-8ad28190-ae2f-4fb5-832f-3ae18e05df81.png)

Usando los datos `dadesBCNMetal.json` y setup `setupDataBCNMetal.json` truncando valor mínimo a 0.1 y multiplicando máximo virtual y por 0.7:

![fase2EdadesMetal](https://user-images.githubusercontent.com/72078368/162377261-80716082-444d-49b1-9e73-22de346e324a.png)

Usando los datos `dadesBCNTransparent.json` y setup `setupDataBCNTransparent.json` truncando valor mínimo a 0.1 y multiplicando máximo virtual y por 0.7:

![fase2EdadesTransparent](https://user-images.githubusercontent.com/72078368/162377392-5b547d9a-0c3e-4635-94c6-af5c5b8d6d5c.png)


* **Fase 3**: 

En este apartado para los apartados guiados de la práctica se han usado las configuraciones indicadas en el guión de la práctica.

Probando los datos `dadesEuropa.json` y setup `setupDataEuropa.json`:

![fase3A1](https://user-images.githubusercontent.com/72078368/162377665-399c4f66-9c32-4fe5-8ef3-ba47b44e9228.png)

Añadiendo MaterialTextura usando los datos `dadesEuropaTextured.json` y setup `setupDataEuropa.json`:

![fase3A2](https://user-images.githubusercontent.com/72078368/162377850-609a9753-7a5a-4d76-84d7-10669946c9b1.png)

Nuevo escenario con cilindros y esferas usando los datos `dadesEuropaFase3.json` y setup `setupDataEuropaFase3.json`:

![fase3A3](https://user-images.githubusercontent.com/72078368/162378030-1fe7f85e-fdb0-4a42-b005-7ad2d89c1d8d.png)


* **Opcionals**:

* <ins>Penombres</ins>: 

   * <ins>Spot light</ins>: 
   
  * <ins>Llum direccional</ins>: 

  * <ins>Ambient Occlusion i Multiple Scattering</ins>:
     
   * <ins>Més d'una propietat en les dades reals</ins>: 
   

   * <ins>Mapejat a esferes</ins>: 

* **Més visualitzacions**:

   * Per totes les imatges, incluiu aqui la imatge obtinguda i els fitxers de dades i de configuració que heu fet servir
