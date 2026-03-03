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
Ver :ref:`DataChangeNotificationCallback <client-function-datachangenotificationcallback>` para más detalles.


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

Se inicializa al conectar a un servidor con :ref:`ConnectAnon <client-function-connectanon>` o :ref:`ConnectUser <client-function-connectuser>`, y se destruye al desconectarse con :ref:`Disconnect <client-function-disconnect>`.

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

Llama a :ref:`Disconnect <client-function-disconnect>` para asegurarse de que el cliente se desconecta del servidor, y se eliminan las suscripciones.
Luego llama al ``Super::EndPlay(EndPlayReason)``.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-tick:

.. rst-class:: classref-method
    
|void| **Tick**\(|float| DeltaTime) |virtual| |override|

Función llamada cada frame.

Llama al ``Super::Tick(DeltaTime)``. 

Si :ref:`IsConnected <client-function-isconnected>` devuelve ``true``, es decir, si el cliente está conectado a un servidor, entonces ejecuta :ref:`ProcessClientEvents <client-function-processclintevents>`.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-connectanon:

.. rst-class:: classref-method

|bool| **ConnectAnon**\(|vconst| `FString`_ URL)

Conecta a un servidor OPC UA de forma anónima, sin credenciales de usuario.

.. warning::
    El servidor al que se conecta debe permitir conexiones anónimas, de lo contrario la conexión fallará.

* URL: Es la dirección del servidor, en el formato ``opc.tcp://IP:PUERTO``. Por ejemplo, ``opc.tcp://192.168.1.100:4840``.

Establece :ref:`Client <client-property-client>` con un nuevo cliente de `open62541`_, e intenta conectar al servidor con las credenciales proporcionadas.
Si se conecta correctamente, establece :ref:`bIsConnected <client-property-isconnected>` a ``true``. Si ocurre un error, destruye el cliente, estableciendo :ref:`Client <client-property-client>` a ``nullptr``.
Devuelve ``true`` si la conexión se establece correctamente, o ``false`` si ocurre un error.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-connectuser:

.. rst-class:: classref-method

|bool| **ConnectUser**\(|vconst| `FString`_ URL, |vconst| `FString`_ Username, |vconst| `FString`_ Password)


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-disconnect:

.. rst-class:: classref-method

|void| **Disconnect**\()


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-isconnected:

.. rst-class:: classref-method

|bool| **IsConnected**\()


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-readnodevalue:

.. rst-class:: classref-method

|bool| **ReadNodeValue**\(|vconst| `FString`_ & NodeIdString, |int32| Namespace, |int32| & OutValue)

.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-execreadnodevalue:

.. rst-class:: classref-method

**execReadNodeValue**\(|vconst| `FString`_ & NodeIdString, |int32| Namespace, |int32| & OutValue)


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-readnodevalueinternal:

.. rst-class:: classref-method

|bool| **ReadNodeValueInternal**\(|vconst| `FString`_ & NodeIdString, |int32| Namespace, |vvoid| OutValue, `FProperty* <FProperty>`_ OutputProperty)


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-writenodevalue:

.. rst-class:: classref-method

|bool| **WriteNodeValue**\(|vconst| `FString`_ & NodeIdString, |int32| Namespace, |int32| InValue)


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-execwritenodevalue:

.. rst-class:: classref-method

**execWriteNodeValue**\(|vconst| `FString`_ & NodeIdString, |int32| Namespace, |int32| InValue)


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-writenodevalueinternal:

.. rst-class:: classref-method

|bool| **WriteNodeValueInternal**\(|vconst| `FString`_ & NodeIdString, |int32| Namespace, |vvoid| InValue, `FProperty* <FProperty>`_ InputProperty)


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-startmonitoringnode:

.. rst-class:: classref-method

|bool| **StartMonitoringNode**\(|vconst| `FString`_ & NodeIdString, |int32| Namespace, |float| SamplingInterval, |int32| & VariableToUpdate, :ref:`FOPCUAOnValueChanged <client-delegate-fopcuaonvaluechanged>` Callback)


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-execstartmonitoringnode:

.. rst-class:: classref-method

**execStartMonitoringNode**\(|vconst| `FString`_ & NodeIdString, |int32| Namespace, |float| SamplingInterval, |int32| & VariableToUpdate, :ref:`FOPCUAOnValueChanged <client-delegate-fopcuaonvaluechanged>` Callback)


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-startmonitoringnodeinternal:

.. rst-class:: classref-method

|bool| **StartMonitoringNodeInternal**\(|vconst| `FString`_ & NodeIdString, |int32| Namespace, |float| SamplingInterval, |int32| & VariableToUpdate, :ref:`FOPCUAOnValueChanged <client-delegate-fopcuaonvaluechanged>` Callback)


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-stopmonitoringnode:

.. rst-class:: classref-method

|bool| **StopMonitoringNode**\(|vconst| `FString`_ & NodeIdString, |int32| Namespace)


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-stopallmonitoring:

.. rst-class:: classref-method

|void| **StopAllMonitoring**\()


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-getnodedatatype:

.. rst-class:: classref-method

`UA_DataType`_ * **GetNodeDataType**\(|vconst| `FString`_ & NodeIdString, |int32| Namespace) |fconst|


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-getnodeid:

.. rst-class:: classref-method

`UA_NodeId`_ **GetNodeId**\(|vconst| `FString`_ & NodeIdString, |int32| Namespace) |fconst|


.. raw:: html
    
    <hr class="classref-item-separator">


.. _client-function-datachangenotificationcallback:

.. rst-class:: classref-method

|void| **DataChangeNotificationCallback**\(`UA_Client`_ * client, `UA_UInt32`_ subId, |vvoid| subContext, `UA_UInt32`_ monId, |vvoid| monContext, `UA_DataValue`_ * value) |static| |cdecl|


.. raw:: html
    
    <hr class="classref-item-separator">

.. _client-function-processclintevents:

.. rst-class:: classref-method

|void| **ProcessClientEvents**\()



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

