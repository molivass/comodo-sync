.. _doc_struct_fmonitoreditem:

FMonitoredItem
===============

.. rst-class:: classref-introduction-group

Descripción
-----------

Estructura que almacena información sobre un nodo monitorizado de un servidor OPC UA.
Para más información sobre suscripciones ver la documentación de la librería: `Subscriptions <https://open62541.org/doc/master/client.html#subscriptions>`_.

.. rst-class:: classref-reftable-group

Propiedades
-----------

.. list-table::
    :widths: 15 35 10

    *   - |uint32|
        - :ref:`MonitoredItemId <fmonitoreditem-property-monitoreditemid>`
        - ``0``
    *   - |uint32|
        - :ref:`SubscriptionId <fmonitoreditem-property-subscriptionid>`
        - ``0``
    *   - `UA_DataType`_\*
        - :ref:`DataType <fmonitoreditem-property-datatype>`
        - ``nullptr``
    *   - `FString`_
        - :ref:`NodeIdString <fmonitoreditem-property-nodeidstring>`
        - ``""``
    *   - |int32|
        - :ref:`Namespace <fmonitoreditem-property-namespace>`
        - ``0``
    *   - |vvoid|
        - :ref:`VarRef <fmonitoreditem-property-varref>`
        - 
    *   - `FName`_
        - :ref:`VarName <fmonitoreditem-property-varname>`
        - ``""``
    *   - :ref:`FOPCUAOnValueChanged <client-delegate-fopcuaonvaluechanged>`
        - :ref:`Callback <fmonitoreditem-property-callback>`
        - 

.. raw:: html

    <hr class="classref-section-separator">

.. rst-class:: classref-reftable-group

Métodos
-----------

.. list-table::
    :widths: 15 90

    *   - |void|
        - :ref:`FMonitoredItem <fmonitoreditem-constructor>`\(|vvoid|\& InRef)

.. raw:: html

    <hr class="classref-section-separator">


.. rst-class:: classref-descriptions-group

Descripciones de Propiedades
----------------------------

.. _fmonitoreditem-property-monitoreditemid:

.. rst-class:: classref-property

|uint32| **MonitoredItemId** = ``0``

Identificador del nodo monitorizado.

El identificador va asociado a una suscripción. 

El valor se obtiene al crear la monitorización con la respuesta de `UA_Client_MonitoredItems_createDataChange`_ .

.. seealso::

    :ref:`SubscriptionId <fmonitoreditem-property-subscriptionid>`



.. raw:: html
    
    <hr class="classref-item-separator">


.. _fmonitoreditem-property-subscriptionid:

.. rst-class:: classref-property

|uint32| **SubscriptionId** = ``0``

Identificador de la suscripción a la que pertenece el nodo monitorizado.

La suscripción puede estar asociada a más de un nodo monitorizado.

El valor se obtiene al crear la suscripción con la respuesta de `UA_Client_Subscriptions_create`_.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _fmonitoreditem-property-datatype:

.. rst-class:: classref-property

`UA_DataType`_\* **DataType** = ``nullptr``

Tipo de datos OPC UA del nodo monitorizado.
El tipo de datos que se espera y se recibe en las notificaciones de cambio de valor. Se asigna automáticamente al crear la monitorización.

.. seealso::

    Ver `UA_DataType`_ para más información sobre los tipos de datos disponibles en OPC UA. 
    Ver :ref:`GetNodeDataType <client-function-getnodedatatype>` para obtener el tipo de datos de un nodo específico.


.. raw:: html
    
    <hr class="classref-item-separator">


.. _fmonitoreditem-property-nodeidstring:

.. rst-class:: classref-property

`FString`_ **NodeIdString** = ``""``

Nombre del nodo del servidor OPC UA que se está monitorizando.

El nombre es único dentro de un namespace concreto, pero se puede repetir entre namespaces.
Se necesita :ref:`Namespace <fmonitoreditem-property-namespace>` para identificar el nodo de forma unívoca en el servidor.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _fmonitoreditem-property-namespace:

.. rst-class:: classref-property

|int32| **Namespace** = ``0``

Número del Namespace en el que se encuentra el nodo monitorizado en el servidor OPC UA.


.. raw:: html
    
    <hr class="classref-item-separator">


.. _fmonitoreditem-property-varref:

.. rst-class:: classref-property

|vvoid| **VarRef**

Puntero a la variable de Unreal. Se actualiza con el valor del nodo monitorizado cada vez que recibe una notificación del servidor.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _fmonitoreditem-property-varname:

.. rst-class:: classref-property

`FName` **VarName** = ``""``

Nombre de la variable de Unreal almacenada en :ref:`VarRef <fmonitoreditem-property-varref>`.

.. deprecated:: 0.1
    
    Este valor ya no se usa y se eliminará en futuras versiones.
    La variable de Unreal se almacena directamente en :ref:`VarRef <fmonitoreditem-property-varref>`.

.. raw:: html
    
    <hr class="classref-item-separator">


.. _fmonitoreditem-property-callback:

.. rst-class:: classref-property

:ref:`FOPCUAOnValueChanged <client-delegate-fopcuaonvaluechanged>` **Callback**

Almacena un delegate de Unreal. Se ejecuta cada vez que el nodo monitorizado recibe una notificación de cambio de valor.

El evento asociado se lanza después de actualizar la variable en :ref:`VarRef <fmonitoreditem-property-varref>`


.. raw:: html

    <hr class="classref-section-separator">


.. rst-class:: classref-descriptions-group

Descripciones de Métodos
----------------------------

.. _fmonitoreditem-constructor:

.. rst-class:: classref-method

|void| **FMonitoredItem**\(|vvoid|\& InRef)

Constructor de la estructura.

Establece todos los miembros a sus valores por defecto, excepto :ref:`VarRef <fmonitoreditem-property-varref>`, que se inicializa con el puntero pasado en el parámetro ``InRef``.


.. _UA_DataType: https://open62541.org/doc/master/types.html#generic-type-handling
.. _FString: https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Core/FString
.. _FName: https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Core/FName
.. _UA_Client_MonitoredItems_createDataChange: https://open62541.org/doc/master/client.html#monitoreditems
.. _UA_Client_Subscriptions_create: https://open62541.org/doc/master/client.html#subscriptions

.. |int32| replace::  :abbr:`int32 (Entero de 32 bits con signo)`
.. |uint32| replace::  :abbr:`uint32 (Entero de 32 bits sin signo)`
.. |vvoid| replace:: :abbr:`void* (Puntero a un valor de cualquier tipo)`
.. |void| replace::  :abbr:`void (Sin valor de retorno)`