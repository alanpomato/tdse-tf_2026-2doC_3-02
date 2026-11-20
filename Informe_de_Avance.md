![Logo Fiuba](LOGO_FIUBA.jpeg)
# Informe de Avance: Máquina Expendedora Inteligente

**Universidad de Buenos Aires — Facultad de Ingeniería**

**Asignatura:** Taller de Sistemas Embebidos (TdSE) — 2026 2C — Curso 3 — Grupo 02

**Fecha:** 19/11/2026

---

Según lo solicitado se comparte el Informe de Avance, detallando el estado actual de todos los requisitos originales enviados en Propuesta.md.

Referencia de colores:

🟢 implementado y probado · 🟡 parcial / en curso · 🔴 pendiente · ⚪ eliminado o reemplazado.

| Grupo | ID | Requisito | Estado | Evidencia / observación |
| :-- | :--: | :-- | :--: | :-- |
| **Compra** | 1.1 | Seleccionar un producto mediante la interfaz local | 🟢 Implementado | Ok mediante botones en task_sensor_btn |
|  | 1.2 | Verificar disponibilidad antes de habilitar la compra | 🟢 Implementado | Ok, con Stock en RAM (ver 4.2). |
|  | 1.3 | Confirmar la compra con un pago simulado | 🟢 Implementado | Monedero simulado con botón, cada pulso suma `VAL_MONEDA` al crédito (en centavos). ENTER confirma. |
|  | 1.4 | Accionar el mecanismo de despacho al confirmar | 🟢 Implementado | `EV_PWM_ON` al canal seleccionado (TIM3 CH1/2/3). |
| **Despacho** | 2.1 | Mecanismo motorizado para entregar productos | 🟡 Parcial / en curso | Firmware y 3 servos SG90 funcionando. |
|  | 2.2 | Sensor óptico de salida del producto | 🟢 Implementado | Barrera IR opertiva. |
|  | 2.3 | Inventario actualizado sólo al confirmar la entrega | 🟢 Implementado | Realizado |
|  | 2.4 | Timeout de entrega → detener e informar falla | 🟢 Implementado | Realizado. |
| **Interfaz** | 3.1 | Botones para seleccionar y confirmar | 🟢 Implementado | Realizado |
|  | 3.2 | Joystick analógico para navegar menús | ⚪ Eliminado | Eliminado: reemplazado por los pulsadores de 3.1 + llave SET_UP (PB15). |
|  | 3.3 | Display con productos, precios, disponibilidad y mensajes | 🟡 Parcial / en curso | LCD 16×2 HD44780 en 4 bits con 7 pantallas definidas. Falta el formato de precio/crédito/stock. |
|  | 3.4 | LEDs y buzzer para estados y fallas | 🟢 Implementado | LED + buzzer pasivo, realizado. |
| **Configuración** | 4.1 | Modo de configuración de precios | 🟢 Implementado | Modo SET_UP: entrada por llave implementada; menú de canal/precio/stock desde display y botonera OK. |
|  | 4.2 | Configuración en Flash interna | 🔴 Pendiente | Modificado a EEPROM externa por I2C1 (PB6/PB7). Pendiente; hoy precios y stock en RAM. |
|  | 4.3 | Recuperar la configuración al iniciar | 🔴 Pendiente | Depende de 4.2. |
| **Comunicación** | 5.1 | Bluetooth LE con HM-10 | 🔴 Pendiente | Pendiente |
|  | 5.2 | Consultar inventario, ventas y recaudación desde la app | 🔴 Pendiente | Los datos ya existen en system, falta el canal. |
|  | 5.3 | Registrar reposición desde la app | 🟡 Parcial / en curso | Primera versión por menú local (SET_UP); BLE después. |
|  | 5.4 | Enviar a la app el resultado de las operaciones | 🔴 Pendiente | Pendiente. |
| **Agregado** | — | Falla por temperatura (sensor analógico por ADC) | 🟡 Parcial / en curso | `TEMP_MAX` = 30 °C con histéresis de 2 grados. |
 
*Tabla 1: Estado de los requisitos de la Propuesta al 19/11/2026.* 