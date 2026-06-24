.. _doc_class_opcuaclient:



AOPCUAClient
============

**Hereda**\: `AActor`_


Clase principal del plugin. 

.. rst-class:: classref-introduction-group

Descripción
-----------

Contiene todas las funciones de conexión a servidores OPC UA, lectura y escritura de nodos, y gestión de suscripciones.

Actúa a modo de `UBlueprintFunctionLibrary`_, pero se define como `AActor`_ para poder pasar el objeto como contexto en las funciones, ya que la librería `open62541`_ requiere de un contexto para monitorizar.
Por defecto Unreal pasa ``self`` como contexto en blueprints, por lo que no afecta a la forma de uso.


.. rst-class:: classref-reftable-group

Propiedades
-----------

.. list-table::
    :widths: 15 35 10

    *   - |bool|
        - :ref:`bIsConnected <client-property-isconnected>`
        - ``false``
    *   - `UA_Client`_ *
        - :ref:`Client <client-property-client>`
        - 
    *   - `TMap`_\<`FString`_, :ref:`FMonitoredItem <doc_struct_fmonitoreditem>`>
        - :ref:`MonitoredItems <client-property-monitoreditems>`
        - 
    

.. rst-class:: classref-reftable-group

Métodos
-----------

.. list-table::
    :widths: 15 90

    *   - |void|
        - :ref:`AOPCUAClient <client-function-constructor>`\()
    *   - |void|
        - :ref:`BeginPlay <client-function-beginplay>`\() |virtual| |override|
    *   - |void|
        - :ref:`EndPlay <client-function-endplay>`\(|vconst| `EEndPlayReason::Type <EndReasonType>`_ EndPlayReason) |virtual| |override|
    *   - |void|
        - :ref:`Tick <client-function-tick>`\(|float| DeltaTime) |virtual| |override|
    *   - |bool|
        - :ref:`ConnectAnon <client-function-connectanon>`\(|vconst| `FString`_ URL)
    *   - |bool|
        - :ref:`ConnectUser <client-function-connectuser>`\(|vconst| `FString`_ URL, |vconst| `FString`_ Username, |vconst| `FString`_ Password)
    *   - |void|
        - :ref:`Disconnect <client-function-disconnect>`\()
    *   - |bool|
        - :ref:`IsConnected <client-function-isconnected>`\()
    *   - |bool|
        - :ref:`ReadNodeValue <client-function-readnodevalue>`\(|vconst| `FString`_\& NodeIdString, |int32| Namespace, |int32| & OutValue)
    *   - 
        - :ref:`execReadNodeValue <client-function-execreadnodevalue>`
    *   - |bool|
        - :ref:`ReadNodeValueInternal <client-function-readnodevalueinternal>`\(|vconst| `FString`_\& NodeIdString, |int32| Namespace, |vvoid| OutValue, `FProperty* <FProperty>`_ OutputProperty)
    *   - |bool|
        - :ref:`WriteNodeValue <client-function-writenodevalue>`\(|vconst| `FString`_\& NodeIdString, |int32| Namespace, |int32| InValue)
    *   - 
        - :ref:`execWriteNodeValue <client-function-execwritenodevalue>`
    *   - |bool|
        - :ref:`WriteNodeValueInternal <client-function-writenodevalueinternal>`\(|vconst| `FString`_\& NodeIdString, |int32| Namespace, |vvoid| InValue, `FProperty* <FProperty>`_ InputProperty)
    *   - |bool|
        - :ref:`StartMonitoringNode <client-function-startmonitoringnode>`\(|vconst| `FString`_\& NodeIdString, |int32| Namespace, |float| SamplingInterval, |int32|\& VariableToUpdate, :ref:`FOPCUAOnValueChanged <client-delegate-fopcuaonvaluechanged>` Callback)
    *   - 
        - :ref:`execStartMonitoringNode <client-function-execstartmonitoringnode>`
    *   - |bool|
        - :ref:`StartMonitoringNodeInternal <client-function-startmonitoringnodeinternal>`\(|vconst| `FString`_\& NodeIdString, |int32| Namespace, |float| SamplingInterval, |vvoid| InValue, `FProperty* <FProperty>`_ InputProperty, :ref:`FOPCUAOnValueChanged <client-delegate-fopcuaonvaluechanged>` Callback)
    *   - |bool|
        - :ref:`StopMonitoringNode <client-function-stopmonitoringnode>`\(|vconst| `FString`_\& NodeIdString, |int32| Namespace)
    *   - |void|
        - :ref:`StopAllMonitoring <client-function-stopallmonitoring>`\()
    *   - `UA_DataType`_\*
        - :ref:`GetNodeDataType <client-function-getnodedatatype>`\(|vconst| `FString`_\& NodeIdString, |int32| Namespace) |fconst|
    *   - `UA_NodeId`_
        - :ref:`GetNodeId <client-function-getnodeid>`\(|vconst| `FString`_\& NodeIdString, |int32| Namespace) |fconst|
    *   - |void|
        - :ref:`DataChangeNotificationCallback <client-function-datachangenotificationcallback>`\(`UA_Client`_\* client, `UA_UInt32`_ subId, |vvoid| subContext, `UA_UInt32`_ monId, |vvoid| monContext, `UA_DataValue`_\* value) |static| |cdecl|
    *   - |void|
        - :ref:`ProcessClientEvents <client-function-processclintevents>`\()  

.. raw:: html

    <hr class="classref-section-separator">


.. rst-class:: classref-descriptions-group

Delegates
-----------

.. _client-delegate-fopcuaonvaluechanged:

.. rst-class:: classref-signal

Dynamic **FOPCUAOnValueChanged**

Delegate dinámico simple.

Ejecuta el evento vinculado cada vez que recibe un cambio de valor de un nodo monitorizado.
Ver :ref:`DataChangeNotificationCallback <client-function-datachangenotificationcallback>`\() para más detalles.


.. raw:: html

    <hr class="classref-section-separator">


.. rst-class:: classref-descriptions-group

Descripciones de Propiedades
----------------------------

.. _client-property-isconnected:

.. rst-class:: classref-property

|bool| **bIsConnected** = ``false``

Devuelve si el cliente está conectado a un servidor o no.
:ref:`Client <client-property-client>` debe estar inicializado para poder conectarse.


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-property-client:

.. rst-class:: classref-property

`UA_Client`_ * **Client** = ``nullptr``

Puntero al cliente de `open62541`_.

Se inicializa al conectar a un servidor con :ref:`ConnectAnon <client-function-connectanon>`\() o :ref:`ConnectUser <client-function-connectuser>`\(), y se destruye al desconectarse con :ref:`Disconnect <client-function-disconnect>`.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-property-monitoreditems:

.. rst-class:: classref-property

`TMap`_\<`FString`_, :ref:`FMonitoredItem <doc_struct_fmonitoreditem>`> **MonitoredItems** = ``{}``

Mapa que almacena los nodos que se están monitorizando. Un nodo monitorizado envía notificaciones al cambiar de valor, lo que permite reaccionar a esos cambios en tiempo real.

La clave es es un `FString`_ con el formato ``NodeIdString:Namespace``

El valor es una estructura :ref:`FMonitoredItem <doc_struct_fmonitoreditem>` que contiene los datos referentes al nodo monitorizado.
Ver la definicón de la estructura para más detalles.


.. raw:: html

    <hr class="classref-section-separator">


.. rst-class:: classref-descriptions-group

Descripciones de Métodos
------------------------

.. _client-function-constructor:

.. rst-class:: classref-method

|void| **AOPCUAClient**\() 

Constructor de la clase.

Establece :ref:`bIsConnected <client-property-isconnected>` a ``false`` y :ref:`Client <client-property-client>` a ``nullptr``.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-beginplay:

.. rst-class:: classref-method

|void| **BeginPlay**\() |virtual| |override|

Función llamada al iniciar el juego o al spawnear el actor.

Simplemente llama al ``Super::BeginPlay()``.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-endplay:

.. rst-class:: classref-method

|void| **EndPlay**\(|vconst| `EEndPlayReason::Type <EndReasonType>`_ EndPlayReason) |virtual| |override|

Función llamada al finalizar el juego o al destruir el actor.

Llama a :ref:`Disconnect <client-function-disconnect>`\() para asegurarse de que el cliente se desconecta del servidor, y se eliminan las suscripciones.
Luego llama al ``Super::EndPlay(EndPlayReason)``.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-tick:

.. rst-class:: classref-method
    
|void| **Tick**\(|float| DeltaTime) |virtual| |override|

Función llamada cada frame.

Llama al ``Super::Tick(DeltaTime)``. 

Si :ref:`IsConnected <client-function-isconnected>`\() devuelve ``true``, es decir, si el cliente está conectado a un servidor, entonces ejecuta :ref:`ProcessClientEvents <client-function-processclintevents>`.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-connectanon:

.. rst-class:: classref-method

|bool| **ConnectAnon**\(|vconst| `FString`_ URL)

Conecta a un servidor OPC UA de forma anónima, sin credenciales de usuario.

.. warning::
    El servidor al que se conecta debe permitir conexiones anónimas, de lo contrario la conexión fallará.

* URL: Es la dirección del servidor, en el formato ``opc.tcp://IP:PUERTO``. Por ejemplo, ``opc.tcp://192.168.1.100:4840``.

Establece :ref:`Client <client-property-client>` con un nuevo cliente de `open62541`_, e intenta conectar al servidor de forma anónima.
Si se conecta correctamente, establece :ref:`bIsConnected <client-property-isconnected>` a ``true``. Si ocurre un error, destruye el cliente, estableciendo :ref:`Client <client-property-client>` a ``nullptr``.
Devuelve ``true`` si la conexión se establece correctamente, o ``false`` si ocurre un error.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-connectuser:

.. rst-class:: classref-method

|bool| **ConnectUser**\(|vconst| `FString`_ URL, |vconst| `FString`_ Username, |vconst| `FString`_ Password)

Conecta a un servidor OPC UA con usuario y contraseña.

.. error::
    Actualmente no funciona y siempre retornará false

* URL: Es la dirección del servidor, en el formato ``opc.tcp://IP:PUERTO``. Por ejemplo, ``opc.tcp://192.168.1.100:4840``.
* Username: El nombre de usuario definido en el servidor
* Password: Contraseña asociada al usuario.

Establece :ref:`Client <client-property-client>` con un nuevo cliente de `open62541`_, e intenta conectar al servidor con las credenciales proporcionadas.
Si se conecta correctamente, establece :ref:`bIsConnected <client-property-isconnected>` a ``true``. Si ocurre un error, destruye el cliente, estableciendo :ref:`Client <client-property-client>` a ``nullptr``.

Devuelve ``true`` si la conexión se establece correctamente, o ``false`` si ocurre un error.


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-disconnect:

.. rst-class:: classref-method

|void| **Disconnect**\()

Desconecta el cliente del servidor.

Llama a :ref:`StopAllMonitoring <client-function-stopallmonitoring>`\() para eliminar las posibles suscripciones,
y se desconecta del servidor en caso de :ref:`Client <client-property-client>` estuviera definido.

Establece :ref:`Client <client-property-client>` a ``null`` y :ref:`bIsConnected <client-property-isconnected>` a ``false``.


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-isconnected:

.. rst-class:: classref-method

|bool| **IsConnected**\()

Devuelve el estado de conexión al servidor.

Devuelve ``true`` si :ref:`Client <client-property-client>` está definido, y :ref:`bIsConnected <client-property-isconnected>` es ``true`` 

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-readnodevalue:

.. rst-class:: classref-method

|bool| **ReadNodeValue**\(|vconst| `FString`_\& NodeIdString, |int32| Namespace, |int32| & OutValue)

Definición para blueprints de :ref:`ReadNodeValueInternal <client-function-readnodevalueinternal>`\().

.. important::
    No se debe llamar a esta función directamente. En Blueprints, se ejecuta :ref:`execReadNodeValue <client-function-execreadnodevalue>`\(),
    que cambia el tipo de OutValue y pasa los valores a :ref:`ReadNodeValueInternal <client-function-readnodevalueinternal>`\().

    En c++ llamar directamente a :ref:`ReadNodeValueInternal <client-function-readnodevalueinternal>`\() con los parámetros necesarios.


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-execreadnodevalue:

.. rst-class:: classref-method

**execReadNodeValue**\()

Ejecución interna de :ref:`ReadNodeValue <client-function-readnodevalue>`\().

.. important::
    La función se ejecuta directamente al llamar a :ref:`ReadNodeValue <client-function-readnodevalue>`\() desde Blueprints.
    Llamar a la función desde c++ puede dar resultados inesperados. Se recomienda llamar a :ref:`ReadNodeValueInternal <client-function-readnodevalueinternal>`\().

Revisa el stack para obtener la dirección de memoria de ``OutValue``, y su `FProperty`_, y se los pasa junto al resto de parámetros a
:ref:`ReadNodeValueInternal <client-function-readnodevalueinternal>`\().


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-readnodevalueinternal:

.. rst-class:: classref-method

|bool| **ReadNodeValueInternal**\(|vconst| `FString`_\& NodeIdString, |int32| Namespace, |vvoid| OutValue, `FProperty* <FProperty>`_ OutputProperty)

Lee el valor actual de un nodo definido en el servidor.

* NodeIdString: El nombre del nodo en el servidor, del cual se quiere leer su valor
* Namespace: El namespace en el que se encuentra el nodo en el servidor
* OutValue: Pin de salida que devuelve el valor obtenido del servidor.
* OutputProperty: Tipo de variable de OutValue. Usado internamente para hacer cast al pin de salida al tipo correspondiente.

La función solo se ejecuta si existe una conexión con un servidor.

Solicita el valor al servidor, hace un cast al tipo correspondiente, y lo devuelve por ``OutValue``.

.. note::
    Actualmente, el tipo de ``OutValue`` y del nodo del servidor deben coincidir exactamente.
    Nótese que en Blueprints las variables de tipo ``float`` son de doble precisión, es decir, el nodo del servidor
    ha de ser de tipo ``double`` o equivalente para poder comunicarse.   

Devuelve ``true`` si se ha conseguido leer el nodo y ``OutValue`` retorna un valor, o ``false`` si ocurre un error, y ``OutValue`` es ``null``

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-writenodevalue:

.. rst-class:: classref-method

|bool| **WriteNodeValue**\(|vconst| `FString`_\& NodeIdString, |int32| Namespace, |int32| InValue)

Definición para blueprints de :ref:`WriteNodeValueInternal <client-function-writenodevalueinternal>`\()

.. important::
    No se debe llamar a esta función directamente. En Blueprints, se ejecuta :ref:`execWriteNodeValue <client-function-execwritenodevalue>`\(),
    que cambia el tipo de InValue y pasa los valores a :ref:`WriteNodeValueInternal <client-function-writenodevalueinternal>`\().

    En c++ llamar directamente a :ref:`WriteNodeValueInternal <client-function-writenodevalueinternal>`\() con los parámetros necesarios.


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-execwritenodevalue:

.. rst-class:: classref-method

**execWriteNodeValue**\()

Ejecución interna de :ref:`WriteNodeValue <client-function-writenodevalue>`\().

.. important::
    La función se ejecuta directamente al llamar a :ref:`WriteNodeValue <client-function-writenodevalue>`\() desde Blueprints.
    Llamar a la función desde c++ puede dar resultados inesperados. Se recomienda llamar a :ref:`WriteNodeValueInternal <client-function-writenodevalueinternal>`\().

Revisa el stack para obtener la dirección de memoria de ``InValue``, y su `FProperty`_, y se los pasa junto al resto de parámetros a
:ref:`WriteNodeValueInternal <client-function-writenodevalueinternal>`\().


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-writenodevalueinternal:

.. rst-class:: classref-method

|bool| **WriteNodeValueInternal**\(|vconst| `FString`_\& NodeIdString, |int32| Namespace, |vvoid| InValue, `FProperty* <FProperty>`_ InputProperty)

Escribe el valor que se pasa como parámetro en un nodo del servidor.

* NodeIdString: El nombre del nodo en el servidor, el cual se quiere cambiar de valor
* Namespace: El namespace en el que se encuentra el nodo en el servidor
* InValue: Valor al que se quiere establecer el nodo.
* InputProperty: Tipo de variable de InValue. Usado internamente para hacer cast al pin de entrada al tipo correspondiente.

La función solo se ejecuta si existe una conexión con un servidor.

Hace cast del valor al tipo equivalente de OPC UA, e intenta escribirlo en el nodo.

.. note::
    Si el tipo de ``InValue`` no coincide con el tipo del nodo del servidor, la escritura fallará.
    Nótese que en Blueprints las variables de tipo ``float`` son de doble precisión, es decir, el nodo del servidor
    ha de ser de tipo ``double`` o equivalente para poder comunicarse.   

Devuelve ``true`` si se ha escrito correctamente, o ``false`` si ocurre un error.


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-startmonitoringnode:

.. rst-class:: classref-method

|bool| **StartMonitoringNode**\(|vconst| `FString`_\& NodeIdString, |int32| Namespace, |float| SamplingInterval, |int32|\& VariableToUpdate, :ref:`FOPCUAOnValueChanged <client-delegate-fopcuaonvaluechanged>` Callback)

Definición para blueprints de :ref:`StartMonitoringNodeInternal <client-function-startmonitoringnodeinternal>`\()

.. important::
    No se debe llamar a esta función directamente. En Blueprints, se ejecuta :ref:`execStartMonitoringNode <client-function-execstartmonitoringnode>`\(),
    que cambia el tipo de VariableToUpdate y pasa los valores a :ref:`StartMonitoringNodeInternal <client-function-startmonitoringnodeinternal>`\().

    En c++ llamar directamente a :ref:`StartMonitoringNodeInternal <client-function-startmonitoringnodeinternal>`\() con los parámetros necesarios.



.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-execstartmonitoringnode:

.. rst-class:: classref-method

**execStartMonitoringNode**\()

Ejecución interna de :ref:`StartMonitoringNode <client-function-startmonitoringnode>`\().

.. important::
    La función se ejecuta directamente al llamar a :ref:`StartMonitoringNode <client-function-startmonitoringnode>`\() desde Blueprints.
    Llamar a la función desde c++ puede dar resultados inesperados. Se recomienda llamar a :ref:`StartMonitoringNodeInternal <client-function-startmonitoringnodeinternal>`\().

Revisa el stack para obtener la dirección de memoria de ``VariableToUpdate``, y su `FProperty`_, y se los pasa junto al resto de parámetros a
:ref:`StartMonitoringNodeInternal <client-function-startmonitoringnodeinternal>`\().

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-startmonitoringnodeinternal:

.. rst-class:: classref-method

|bool| **StartMonitoringNodeInternal**\(|vconst| `FString`_\& NodeIdString, |int32| Namespace, |float| SamplingInterval, |vvoid| InValue, `FProperty* <FProperty>`_ InputProperty, :ref:`FOPCUAOnValueChanged <client-delegate-fopcuaonvaluechanged>` Callback)

Inicia la monitorización de un nodo del servidor. Actualiza la variable que se pasa como parámetro automáticamente cada vez que el nodo cambia de valor en el servidor.

* NodeIdString: El nombre del nodo del servidor que se quiere monitorizar
* Namespace: El namespace en el que se encuentra el nodo en el servidor
* SamplingInterval: Intervalo en milisegundos entre peticiones al servidor para recibir actualizaciones.
* InValue: Variable que la función actualizará cada vez que reciba un nuevo valor del servidor.
* InputProperty: Tipo de variable de ``InValue``. Usado internamente para hacer cast al pin de entrada al tipo correspondiente.
* Callback: Delegate que se ejecutará tras cambiar el valor de ``InValue``. Conectar el pin en Blueprints es opcional.

La función solo se ejecuta si existe una conexión con un servidor.

Si ya se está monitorizando el nodo, la función devuelve ``false`` con un mensaje indicativo.

Crea una suscripción y comienza la monitorización del nodo. Se pasa la función :ref:`DataChangeNotificationCallback <client-function-datachangenotificationcallback>`\() al crear la monitorización,
que se ejecuta cada vez que se recibe un cambio del servidor.
Almacena la referencia a la monitorización en :ref:`MonitoredItems <client-property-monitoreditems>`

La función devuelve ``true`` si se ha empezado a monitorizar el nodo correctamente.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-stopmonitoringnode:

.. rst-class:: classref-method

|bool| **StopMonitoringNode**\(|vconst| `FString`_\& NodeIdString, |int32| Namespace)

Detiene la monitorización de un nodo.

* NodeIdString: El nombre del nodo en el servidor, el cual se quiere dejar de monitorizar
* Namespace: El namespace en el que se encuentra el nodo en el servidor

Si el nodo no existe en :ref:`MonitoredItems <client-property-monitoreditems>`, la función devuelve ``false``.
En caso contrario, intenta eliminar la monitorización del nodo. Si no hay más nodos monitorizados bajo la misma suscripción, también elimina la suscripción.
Finalmente elimina la referencia a la monitorización de :ref:`MonitoredItems <client-property-monitoreditems>`.

Devuelve ``true`` si se ha terminado la monitorización correctamente, o ``false`` si hubo un error.


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-stopallmonitoring:

.. rst-class:: classref-method

|void| **StopAllMonitoring**\()

Llama a :ref:`StopMonitoringNode <client-function-stopmonitoringnode>`\() para cada elemento de :ref:`MonitoredItems <client-property-monitoreditems>`.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-getnodedatatype:

.. rst-class:: classref-method

`UA_DataType`_ * **GetNodeDataType**\(|vconst| `FString`_\& NodeIdString, |int32| Namespace) |fconst|

Obtiene el `UA_DataType`_ de un nodo a partir de su nombre.

* NodeIdString: El nombre del nodo en el servidor
* Namespace: El namespace en el que se encuentra el nodo en el servidor

La función solo se ejecuta si existe una conexión con un servidor. 

Devuelve el `UA_DataType`_ del nodo si existe un nodo con ese nombre, o ``nullptr`` si falla.


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-getnodeid:

.. rst-class:: classref-method

`UA_NodeId`_ **GetNodeId**\(|vconst| `FString`_ & NodeIdString, |int32| Namespace) |fconst|

Crea y devuelve un `UA_NodeId`_ a partir del nombre del nodo

* NodeIdString: El nombre del nodo en el servidor
* Namespace: El namespace en el que se encuentra el nodo en el servidor

Si no existe :ref:`Client <client-property-client>` la función devuelve ``UA_NODEID_NULL``

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-datachangenotificationcallback:

.. rst-class:: classref-method

|void| **DataChangeNotificationCallback**\(`UA_Client`_\* client, `UA_UInt32`_ subId, |vvoid| subContext, `UA_UInt32`_ monId, |vvoid| monContext, `UA_DataValue`_\* value) |static| |cdecl|

Función interna. Es llamada automáticamente al recibir un cambio de valor de un nodo monitorizado.

* Client: El cliente conectado al servidor. :ref:`Client <client-property-client>`
* subId: Id de suscripción. :ref:`FMonitoredItem <doc_struct_fmonitoreditem>`\.\ :ref:`SubscriptionId <fmonitoreditem-property-subscriptionid>`
* subContext: Contexto de la suscripción. Debe ser un :ref:`AOPCUAClient <doc_class_opcuaclient>` ``this`` en c++, ``self`` en Blueprints llamando desde un actor :ref:`AOPCUAClient <doc_class_opcuaclient>`. 
* monId: Id de la monitorización. :ref:`FMonitoredItem <doc_struct_fmonitoreditem>`\.\ :ref:`MonitoredItemId <fmonitoreditem-property-monitoreditemid>`
* monContext: Contexto de la monitorización. No se usa actualmente, puede ser ``NULL``
* value: El nuevo valor que retorna el nodo del servidor.

La función solo se ejecuta si se ha pasado un contexto de subscripción válido, de clase :ref:`AOPCUAClient <doc_class_opcuaclient>`,
y el puntero de ``value`` no es nulo.

Busca un elemento en :ref:`MonitoredItems <client-property-monitoreditems>` cuyas id de subscripción y monitorización coincidan con ``subId`` y ``monId`` respectivamente.
Si existe, intenta hacer cast a la variable :ref:`FMonitoredItem <doc_struct_fmonitoreditem>`\.\ :ref:`VarRef <fmonitoreditem-property-varref>` al mismo tipo que el nodo del servidor,
y establece su valor al nuevo recibido en ``value``.

.. note::
    Si el tipo de la variable no coincide con el tipo del nodo del servidor, la escritura fallará.
    Nótese que en Blueprints las variables de tipo ``float`` son de doble precisión, es decir, el nodo del servidor
    ha de ser de tipo ``double`` o equivalente para poder comunicarse.

Tras actualizar la variable, lanza el delegate de :ref:`FMonitoredItem <doc_struct_fmonitoreditem>`\.\ :ref:`Callback <fmonitoreditem-property-callback>`.

.. raw:: html
    
    <hr class="classref-item-separator">

.. _client-function-processclintevents:

.. rst-class:: classref-method

|void| **ProcessClientEvents**\()

La función solo se ejecuta si :ref:`Client <client-property-client>` está definido.

Llama a `UA_client_run_iterate`_ para asegurar que los eventos asíncronos y otras tareas de la librería se ejecutan. Mantiene la conexión con el servidor estable.


.. _AActor: https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/AActor
.. _UBlueprintFunctionLibrary: https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/UBlueprintFunctionLibrary
.. _EndReasonType: https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/EEndPlayReason__Type
.. _FString: https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Core/FString
.. _FProperty: https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/CoreUObject/FProperty
.. _open62541: https://open62541.org/
.. _UA_DataType: https://open62541.org/doc/master/types.html#generic-type-handling
.. _UA_NodeId: https://open62541.org/doc/master/types.html#nodeid
.. _UA_Client: https://open62541.org/doc/master/client.html
.. _UA_UInt32: https://open62541.org/doc/master/types.html#uint32
.. _UA_DataValue: https://open62541.org/doc/master/types.html#datavalue
.. _UA_Client_run_iterate: https://open62541.org/doc/master/client.html#client
.. _TMap: https://dev.epicgames.com/documentation/en-us/unreal-engine/map-containers-in-unreal-engine

.. |void| replace::  :abbr:`void (Sin valor de retorno)`
.. |vvoid| replace:: :abbr:`void* (Puntero a un valor de cualquier tipo)`
.. |float| replace::  :abbr:`float (Valor de punto flotante. Precisión simple)`
.. |bool| replace::  :abbr:`bool (Valor booleano, verdadero o falso)`
.. |int32| replace::  :abbr:`int32 (Entero de 32 bits con signo)`
.. |virtual| replace::  :abbr:`virtual (Función que puede ser sobreescrita en clases hijas)`
.. |override| replace::  :abbr:`override (Función que sobreescribe una función virtual de la clase padre)`
.. |static| replace:: :abbr:`static (Función que pertenece a la clase en lugar de a una instancia)`
.. |cdecl| replace:: :abbr:`__cdecl (Convención de llamada estándar de C)`
.. |fconst| replace:: :abbr:`const (No modifica ninguna de las variables miembro de la instancia)`
.. |vconst| replace::  :abbr:`const (El parámetro no puede ser modificado dentro de la función)`

