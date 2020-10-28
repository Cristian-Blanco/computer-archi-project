# Arquitectura de Computadores y Laboratorio
# Integrantes:
# Christian Yesid Galindo Cano - 20181020111
# Cristian Javier Martínez Blanco - 20182020155

def recibirProposicion():
    global proposicion, nombres_letras_becedario
    proposicion = proposicion.replace("<-->", "<->")
    proposicion = proposicion.replace("<=>", "<->")
    proposicion = proposicion.replace("<==>", "<->")
    proposicion = proposicion.replace("=>", "->")
    proposicion = proposicion.replace("[", "(")
    proposicion = proposicion.replace("]", ")")
    proposicion = proposicion.replace("}", ")")
    proposicion = proposicion.replace("{", "(")
    
    for i in range (len(proposicion)):
        if (proposicion[i] in nombresProposicion) and (proposicion[i] in Variables)==False: Variables.append(proposicion[i])
    Variables.sort()
    for i in range(len(Variables)):
        nombres_letras_becedario = nombres_letras_becedario.replace(Variables[i],"")
    proposicion = concatenarProposicion(proposicion)

def concatenarProposicion(cadena):
    i = 0
    aux = len(cadena)
    while i<aux-1:
        if (cadena[i] in Variables) and cadena[i+1] in Variables:
            cadena = cadena.replace(cadena[i]+cadena[i+1],cadena[i]+"^"+cadena[i+1])
            i = 0
            aux = len(cadena)
        else: i += 1
    return cadena

def generarTabladeVerdad():
    print ("\n\t\t\tTABLA DE VERDAD\n")
    print ("\t",)
    for i in range(len(Variables)):
        if Variables[i] in Lista_Alias: print ("|", Lista_Alias.index(Variables[i])+1,end="")
        else: print ("|", Variables[i],end="")
    print ("|\n")
    
    for i in range(Tamanio+1):
        print ("\t")
        for j in range(len(Renglon[i])):
            if Variables[j] in Lista_Alias and (Lista_Alias.index(Variables[j])+1) >= 10:
                if j == 0: print ("|",end="")
                print (Renglon[i][j], " |",end="")
            else:
                if j == 0: print ("|",end="")
                print (Renglon[i][j], "|",end="")
        print ("\n")
        
def combinacionesDistintas(size):
    aux = 0
    if size ==1:
        for i in range(2):
            Renglon[aux].append(i)
            aux += 1
    if size==2:
        for i in range(2):
           for j in range(2):
               Renglon[aux].append(i)
               Renglon[aux].append(j)
               aux += 1
    if size == 3:
        for i in range(2):
            for j in range(2):
                for k in range(2):
                    Renglon[aux].append(i)
                    Renglon[aux].append(j)
                    Renglon[aux].append(k)
                    aux += 1

def parentesisSeparador(cadena):
    global proposicion, contador
    global charx
    nuevaproposicion = ""
    if ("(" in cadena):
        for i in range(cadena.find("(")+1,len(cadena)):
            nuevaproposicion = nuevaproposicion + cadena[i]
        parentesisSeparador(nuevaproposicion)
    elif (")" in cadena):
        i = 0
        while cadena[i] != ")":
            nuevaproposicion = nuevaproposicion + cadena[i]
            i += 1
        calcularResultado(nuevaproposicion)
        proposicion = proposicion.replace("(" + nuevaproposicion + ")", nombres_letras_becedario[contador])
        proposicion = concatenarProposicion(proposicion)
        Alias[contador] = "(" + nuevaproposicion + ")"
        parentesisSeparador(proposicion)
    else: calcularResultado(cadena)

def calcularResultado(cadena):
    global contador
    aux = ""
    ok = 0
    if "~" in cadena:
        if cadena[cadena.find("~")+1] == "~":
            for it in range(len(cadena)):
                if cadena[it] == "~" and ok == 0:
                    aux += "!"
                    ok = 1
                else: aux += cadena[it]
            calcularResultado(aux)
        else:
            for i in range(Tamanio):
                aux = operadorNegar(Renglon[i][Variables.index(cadena[cadena.find("~") + 1])])
                Renglon[i].append(aux)
            contador += 1
            Alias[contador] = "~" + cadena[cadena.find("~") + 1]
            Lista_Alias.append(nombres_letras_becedario[contador])
            Variables.append(nombres_letras_becedario[contador])
            cadena = cadena.replace(Alias[contador], nombres_letras_becedario[contador])
            cadena = cadena.replace("!", "~")
            calcularResultado(cadena)
    elif "^" in cadena:
        for i in range(Tamanio):
            aux = operadorAnd(Renglon[i][Variables.index(cadena[cadena.find("^")-1])],Renglon[i][Variables.index(cadena[cadena.find("^")+1])])
            Renglon[i].append(aux)
        contador += 1
        Alias[contador] = cadena[cadena.find("^") - 1] + "^" + cadena[cadena.find("^") + 1]
        entradaDeProceso(cadena)
    elif "V" in cadena:
        for i in range(Tamanio):
            aux = operadorOr(Renglon[i][Variables.index(cadena[cadena.find("V")-1])],Renglon[i][Variables.index(cadena[cadena.find("V")+1])])
            Renglon[i].append(aux)
        contador +=1
        Alias[contador] = cadena[cadena.find("V")-1]+"V"+cadena[cadena.find("V")+1]
        entradaDeProceso(cadena)
    elif "<->" in cadena:
        for i in range(Tamanio):
            aux = operadorBicondicional(Renglon[i][Variables.index(cadena[cadena.find("<")-1])],Renglon[i][Variables.index(cadena[cadena.find(">")+1])])
            Renglon[i].append(aux)
        contador += 1
        Alias[contador] = cadena[cadena.find("<") - 1] + "<->" + cadena[cadena.find(">") + 1]
        entradaDeProceso(cadena)
    elif "->" in cadena:
        for i in range(Tamanio):
            aux = operadorCondicional(Renglon[i][Variables.index(cadena[cadena.find("-")-1])],Renglon[i][Variables.index(cadena[cadena.find(">")+1])])
            Renglon[i].append(aux)
        contador += 1
        Alias[contador] = cadena[cadena.find("-") - 1] + "->" + cadena[cadena.find(">") + 1]
        entradaDeProceso(cadena)



def entradaDeProceso(cadena):
    global contador
    Lista_Alias.append(nombres_letras_becedario[contador])
    Variables.append(nombres_letras_becedario[contador])
    cadena = cadena.replace(Alias[contador], nombres_letras_becedario[contador])
    calcularResultado(cadena)


def operadorBicondicional(x,y):
    if (x == 1 and y == 1) or (x == 0 and y == 0): return 1
    else: return 0

def operadorCondicional(x,y):
    if (x == 1 and y == 0): return 0
    else: return 1

def operadorNegar(x):
    if x == 0: return 1
    if x == 1: return 0

def operadorOr(x,y):
    if x== 1 or y == 1: return 1
    else: return 0

def operadorAnd(x,y):
    if x ==1 and y ==1: return 1
    else: return 0

def arreglarLetrasAbecedario():
    for i in range(len(Lista_Alias)):
        for j in range(len(Alias[i+1])):
            if Alias[i + 1][j] in Lista_Alias:
                Alias[i+1] = Alias[i+1].replace(Alias[i+1][j],Alias[Lista_Alias.index(Alias[i + 1][j])+1])
                arreglarLetrasAbecedario()

def definirVariableTipo():
    visor0 = 0
    visor1 = 0
    for i in range(Tamanio):
        if Renglon[i][len(Variables)-1] == 0: visor0 += 1
        elif Renglon[i][len(Variables)-1] == 1: visor1 += 1
    if visor0 == Tamanio: print ("\t\tContradicción\n\t\tLa proposicion",Alias[len(Lista_Alias)].replace(" XOR ", "(+)"),"es falsa.")
    elif visor1 == Tamanio: print ("\t\tTautología\n\t\tLa proposicion",Alias[len(Lista_Alias)].replace(" XOR ", "(+)"),"es verdadera.")
    else: print ("\t\tContingencia\n\t\tLa proposicion",Alias[len(Lista_Alias)].replace(" XOR ", "(+)"),"puede ser falsa o verdadera.")

def Main():
    global Tamanio, proposicion,proposicion_original
    proposicion =input("\tIngresa la proposicion logica en su forma formal o informal:\n\t")
    proposicion_original = proposicion
    proposicion = proposicion.upper()
    recibirProposicion()
    Tamanio = 2 ** (len(Variables))
    for i in range(100):
        Renglon.append([])
        Alias.append([])
    combinacionesDistintas(len(Variables))
    parentesisSeparador(proposicion)
    arreglarLetrasAbecedario()
    print ("\n\tProposicion ingresada:\n\t", proposicion_original)
    print ("\n\tProposicion formalizada:\n\t", Alias[len(Lista_Alias)].replace(" XOR ", "(+)"))
    print ("\n\tNumero de combinaciones:", Tamanio)
    print ("\n\tConsidere:\n")
    for i in range(len(Lista_Alias)):
        print ("\t\t", i + 1, "->", Alias[i + 1].replace(" XOR ", "(+)"))
    generarTabladeVerdad()
    definirVariableTipo()

def Menu():
    try:
        Inicializar()
        Main()
        opc = input("\n\tIngresar nueva proposicion:\n\t\t1.- Si\n\t\t2.- No\n\t\t")
        print ("\n")
        if opc == "1": Menu()
    except:
        print ("\tHa ocurrido un error, intente de nuevo\n\t","Revise: '",proposicion_original,"' al convertir a '",proposicion,"'")
        Menu()

def Inicializar():
    global Tamanio,contador,charx, nombres_letras_becedario,proposicion_original
    proposicion_original = ""
    nombres_letras_becedario = ' abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNPQRSTVUXYZ0123456789!#$"%&/()=?{}-.'
    while len(Variables)>0: Variables.pop()
    while len(Alias)>0: Alias.pop()
    while len(Lista_Alias)>0: Lista_Alias.pop()
    while len(Renglon)>0: Renglon.pop()
    Tamanio = contador = 0
    charx = ""


#VARIABLES GLOBALES
nombresProposicion = "ABCDEFGHIJKLMNPQRSTUXZ"
proposicion_original = ""
nombres_letras_becedario = ' abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNPQRSTVUXYZ0123456789#$"%&/()=?{}-.'
Variables = []
Alias = []
Lista_Alias = []
Operadores = []
Renglon = []
charx = ""
contador = 0
Tamanio = 0
proposicion = ""


print ("""

                        TABLA DE VERDAD DE UNA PROPOPOSICION LOGICA

        OPERADORES ACEPTADOS PARA:

            Parentesis  :   (), []
            Negacion    :   ~
            Conjuncion  :   ^
            Disyuncion  :   v
            Condicional :   ->, =>
            Bicondicional:  <->,<-->, <=>, <==>

        #Nota:  Se pueden ocupar espacios, no hay distincion
                entre MAYUSCULAS y minusculas.
                Se admite un maximo de 3 variables.
        
            """)
Menu()
