{
  "graph": {
    "cells": [
      {
        "position": {
          "x": 0,
          "y": 0
        },
        "size": {
          "height": 10,
          "width": 10
        },
        "type": "Statechart",
        "id": "00ffb6d1-d225-4bc0-8b73-7df9987f57b7",
        "attrs": {
          "name": {
            "text": "system_statechart Export Export"
          },
          "specification": {
            "text": "@EventDriven\r\n@SuperSteps(no)\r\ninterface:\r\n    // === 1. EVENTOS DE ENTRADA (Por Cola de Eventos) ===\r\n    in event EV_SYS_NEXT       // Seleccionar producto / Avanzar opción (Next)\r\n    in event EV_SYS_ENTER      // Confirmar compra / Entrar en menú (Enter)\r\n    in event EV_SYS_ESC     // Cancelar operación / Volver atrás (Escape)\r\n    in event EV_SYS_SETUP      // Botón azul / Switch para entrar o salir de SET_UP\r\n    in event EV_SYS_NORMAL     // Botón de retorno al modo normal\r\n    \r\n    in event EV_SYS_MONEDA // el evento de que entra una moneda\r\n    \r\n\r\n    // Desde Task_Sensor_ADC (Barrera óptica LED + LDR)\r\n    in event EV_SYS_ENTREGADO      // Detecta caída del producto en el canal\r\n\r\n    // Desde Task_Comm (Bluetooth HM-10 por UART)\r\n    in event EV_SYS_COMM_RX        // Llegó comando al buffer (STOCK?, REPO, PRECIO, etc.)\r\n\r\n    // === 2. DATOS DE ENTRADA (Interfaz Flag / Dato desde Task_Sensor_ADC) ===\r\n    var temperatura: integer = 20  // Potenciómetro de temperatura de cabina (°C)\r\n    const TEMP_MAX: integer = 30   // Umbral máximo de temperatura antes de bloquear\r\n\r\n    // === 3. VARIABLES INTERNAS DE TASK_SYSTEM (dta y EEPROM) ===\r\n    var prod_idx: integer = 0      // Producto seleccionado (0: Prod 1, 1: Prod 2, 2: Prod 3)\r\n    var param_idx: integer = 0     // Parámetro en SET_UP (0: Precio, 1: Stock)\r\n    var tick: integer = 0          // Contador para timeouts no bloqueantes (en ms o seg)\r\n\r\n    // Variables globales de operación (Declaradas UNA sola vez)\r\n    var credito: integer = 0       // Monedero actual disponible ($)\r\n    var recaudado: integer = 0     // Recaudación acumulada ($)\r\n    var q_ventas: integer = 0      // Cantidad total de ventas realizadas\r\n    const MONEDA: integer = 50\r\n\r\n    // Precios de cada producto de forma independiente\r\n    var p0_precio: integer = 100\r\n    var p1_precio: integer = 150\r\n    var p2_precio: integer = 200\r\n\r\n    // Stock de cada producto de forma independiente\r\n    var p0_stock: integer = 10\r\n    var p1_stock: integer = 9\r\n    var p2_stock: integer = 8\r\n\r\n    // === 4. SALIDAS HACIA ACTUADORES, DRIVERS Y COMUNICACIÓN ===\r\n    // Hacia Task_Actuator_DISPLAY (Interfaz de Dato / Flag)\r\n    var texto_a_imprimir: integer = 0  // ID de pantalla (0:Espera, 1:Seleccion, 2:Entregando, 3:Error, 4:Setup, 5:Atasco, 6:Temp)\r\n    var servo_id: integer = 0\r\n    // Hacia Task_Actuator_PWM (Cola de Eventos: EV_ON / EV_OFF + ID_SERVO)\r\n    out event EV_ON_SERVO\r\n    out event EV_OFF_SERVO\r\n\r\n    // Hacia Task_Actuator_GPIO (Cola de Eventos: LED Disponible y Buzzer Despacho)\r\n    out event EV_ON_LED         // Máquina disponible (NORMAL)\r\n    out event EV_BLINK_LED      // Titila mientras entrega producto (ENTREGANDO)\r\n    out event EV_OFF_LED        // Máquina no disponible (FALLA / SET_UP)\r\n    out event EV_ON_BUZZER      // Suena en ENTREGANDO o en alerta de ATASCO\r\n    out event EV_OFF_BUZZER     // Apaga el buzzer\r\n\r\n    // Hacia Driver eeprom.c y Task_Comm\r\n    out event eeprom_read\r\n    out event eeprom_write\r\n    out event EV_COMM_TX           // Envía respuesta por cola de mensajes a Task_Comm"
          }
        },
        "z": 1
      },
      {
        "position": {
          "x": -1350,
          "y": -463
        },
        "size": {
          "width": 1109,
          "height": 454
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "NORMAL",
            "fontSize": 11
          },
          "specification": {
            "text": "entry / raise EV_OFF_BUZZER\nEV_SYS_MONEDA / credito += MONEDA"
          }
        },
        "id": "b907b8c2-5dd0-4964-8c42-0947d1d1110d",
        "z": 4,
        "embeds": [
          "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
        ]
      },
      {
        "position": {
          "x": -1347,
          "y": -404
        },
        "size": {
          "width": 1103,
          "height": 392
        },
        "type": "Region",
        "attrs": {
          "priority": {
            "text": 1
          }
        },
        "id": "3cd66b33-3c9b-4f04-babf-c466f5974ccc",
        "z": 5,
        "embeds": [
          "4d02c6a1-2844-4c75-8ba6-f372190f699d",
          "29c08a81-57ec-4a4a-88f3-b66a1821df94",
          "a3f8976b-5c3c-4b52-b36d-8499db880d17",
          "0f360775-109d-40f4-a2c1-7b2812409c78",
          "433f306b-a8a2-4de4-84e4-0ef23ff1977d",
          "a08405bf-dad0-485b-82c4-a877ff6b3b7d",
          "df447db0-42bd-4b4c-9118-11a0a4c3e4c7",
          "0047a7df-92d9-4c34-8fce-5d72172e5e7b",
          "365f0cf2-fe33-44e9-8676-e75009276762",
          "937ddc45-9732-472b-bfde-e4bcc35809d7",
          "002b3213-2b67-4e93-8169-4e8c6f6f5a5a",
          "22b8bc87-1293-48eb-9333-a26772d67d59",
          "646e70e7-2be4-4a03-9df3-43da1ad21984",
          "35ac954e-c399-4bce-91a3-ddf0ad4ebba2"
        ],
        "parent": "b907b8c2-5dd0-4964-8c42-0947d1d1110d"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "22b8bc87-1293-48eb-9333-a26772d67d59"
        },
        "target": {
          "id": "646e70e7-2be4-4a03-9df3-43da1ad21984",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "99.039%",
              "dy": "18.333%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "[(prod_idx == 0 && p0_stock > 0 && credito >= p0_precio) ||\n(prod_idx == 1 && p1_stock > 0 && credito >= p1_precio) ||\n(prod_idx == 2 && p2_stock > 0 && credito >= p2_precio)]"
              }
            },
            "position": {
              "distance": 0,
              "offset": 40.553406058164846,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "29c08a81-57ec-4a4a-88f3-b66a1821df94",
        "z": 6,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": -498,
            "y": -152.47
          }
        ],
        "parent": "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "646e70e7-2be4-4a03-9df3-43da1ad21984"
        },
        "target": {
          "id": "002b3213-2b67-4e93-8169-4e8c6f6f5a5a",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "51.81%",
              "dy": "93.333%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_ENTREGADO / \n    p0_stock = (prod_idx == 0) ? p0_stock - 1 : p0_stock;\n    p1_stock = (prod_idx == 1) ? p1_stock - 1 : p1_stock;\n    p2_stock = (prod_idx == 2) ? p2_stock - 1 : p2_stock;\n    recaudado += (prod_idx == 0) ? p0_precio : ((prod_idx == 1) ? p1_precio : p2_precio);\n    credito -= (prod_idx == 0) ? p0_precio : ((prod_idx == 1) ? p1_precio : p2_precio);\n    q_ventas += 1;\n    raise eeprom_write"
              }
            },
            "position": {
              "distance": 0.3507559447161919,
              "offset": 268.999970703125,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "a3f8976b-5c3c-4b52-b36d-8499db880d17",
        "z": 7,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "365f0cf2-fe33-44e9-8676-e75009276762"
        },
        "target": {
          "id": "22b8bc87-1293-48eb-9333-a26772d67d59"
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_ENTER"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "0f360775-109d-40f4-a2c1-7b2812409c78",
        "z": 8,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": -358,
            "y": -342
          }
        ],
        "parent": "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "22b8bc87-1293-48eb-9333-a26772d67d59"
        },
        "target": {
          "id": "937ddc45-9732-472b-bfde-e4bcc35809d7",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "90.258%",
              "dy": "50%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {
              "distance": 0.5388611570630355,
              "offset": 4.815475463867216,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "433f306b-a8a2-4de4-84e4-0ef23ff1977d",
        "z": 9,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": -586,
            "y": -43
          },
          {
            "x": -834,
            "y": -43
          }
        ],
        "parent": "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "937ddc45-9732-472b-bfde-e4bcc35809d7"
        },
        "target": {
          "id": "002b3213-2b67-4e93-8169-4e8c6f6f5a5a",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "7.971%",
              "dy": "85%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "after 5 s"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "a08405bf-dad0-485b-82c4-a877ff6b3b7d",
        "z": 11,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "365f0cf2-fe33-44e9-8676-e75009276762"
        },
        "target": {
          "id": "002b3213-2b67-4e93-8169-4e8c6f6f5a5a",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "98.04%",
              "dy": "83.333%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_ESC, after 15 s"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "df447db0-42bd-4b4c-9118-11a0a4c3e4c7",
        "z": 12,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "002b3213-2b67-4e93-8169-4e8c6f6f5a5a"
        },
        "target": {
          "id": "365f0cf2-fe33-44e9-8676-e75009276762",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "3.449%",
              "dy": "50%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_NEXT/ prod_idx = 0"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "0047a7df-92d9-4c34-8fce-5d72172e5e7b",
        "z": 13,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
      },
      {
        "position": {
          "x": -682,
          "y": -350
        },
        "size": {
          "width": -1,
          "height": -1
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "SELECCION",
            "fontSize": 11
          },
          "specification": {
            "text": "entry / texto_a_imprimir = 1"
          }
        },
        "id": "365f0cf2-fe33-44e9-8676-e75009276762",
        "z": 14,
        "embeds": [
          "f1038f4c-9c36-4cd5-bb33-7115e3517ba9"
        ],
        "parent": "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "365f0cf2-fe33-44e9-8676-e75009276762",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "6.324%",
              "dy": "8.333%",
              "rotate": true
            }
          },
          "priority": true
        },
        "target": {
          "id": "365f0cf2-fe33-44e9-8676-e75009276762",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "96.007%",
              "dy": "0%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_NEXT / prod_idx = (prod_idx + 1) % 3"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "f1038f4c-9c36-4cd5-bb33-7115e3517ba9",
        "z": 15,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "365f0cf2-fe33-44e9-8676-e75009276762"
      },
      {
        "position": {
          "x": -1125,
          "y": -83
        },
        "size": {
          "width": -1,
          "height": -1
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "SIN_STOCK_FALTA_CREDITO",
            "fontSize": 11
          },
          "specification": {
            "text": "entry / texto_a_imprimir = 3"
          }
        },
        "id": "937ddc45-9732-472b-bfde-e4bcc35809d7",
        "z": 16,
        "parent": "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
      },
      {
        "position": {
          "x": -1261,
          "y": -350
        },
        "size": {
          "width": -1,
          "height": -1
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "ESPERA",
            "fontSize": 11
          },
          "specification": {
            "text": "entry / texto_a_imprimir = 0; prod_idx = 0; raise EV_ON_LED"
          }
        },
        "id": "002b3213-2b67-4e93-8169-4e8c6f6f5a5a",
        "z": 17,
        "parent": "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
      },
      {
        "position": {
          "x": -384,
          "y": -163
        },
        "size": {
          "width": 15,
          "height": 15
        },
        "type": "Choice",
        "attrs": {},
        "id": "22b8bc87-1293-48eb-9333-a26772d67d59",
        "z": 20,
        "parent": "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
      },
      {
        "position": {
          "x": -1217,
          "y": -177
        },
        "size": {
          "width": 663,
          "height": 62
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "ENTREGANDO",
            "fontSize": 11
          },
          "specification": {
            "text": "entry / texto_a_imprimir = 2; servo_id = prod_idx; raise EV_ON_SERVO; raise EV_BLINK_LED; raise EV_ON_BUZZER\nexit / raise EV_OFF_SERVO; raise EV_OFF_BUZZER"
          }
        },
        "id": "646e70e7-2be4-4a03-9df3-43da1ad21984",
        "z": 21,
        "parent": "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
      },
      {
        "position": {
          "x": -161,
          "y": -129
        },
        "size": {
          "width": 781,
          "height": 176
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "FALLA",
            "fontSize": 11
          },
          "specification": {
            "text": "entry / raise EV_OFF_LED"
          }
        },
        "id": "73918de9-820e-4462-9850-f35d5d4328c2",
        "z": 96,
        "embeds": [
          "c69f044a-5a5f-49bc-b9d0-53f522188f3d"
        ]
      },
      {
        "position": {
          "x": -158,
          "y": -84
        },
        "size": {
          "width": 775,
          "height": 128
        },
        "type": "Region",
        "attrs": {
          "priority": {
            "text": 1
          }
        },
        "id": "c69f044a-5a5f-49bc-b9d0-53f522188f3d",
        "z": 97,
        "embeds": [
          "a2f00d77-d816-4cd3-ae35-b5b9999d1ddd",
          "63206253-529b-498c-831f-91fbb55f7885",
          "1f2149b1-b432-4ceb-a79f-5068563418b0",
          "aa3bbee3-1caf-427b-b625-e814d0bb65a4"
        ],
        "parent": "73918de9-820e-4462-9850-f35d5d4328c2"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "aa3bbee3-1caf-427b-b625-e814d0bb65a4"
        },
        "target": {
          "id": "1f2149b1-b432-4ceb-a79f-5068563418b0",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "42.625%",
              "dy": "5%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "a2f00d77-d816-4cd3-ae35-b5b9999d1ddd",
        "z": 98,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "c69f044a-5a5f-49bc-b9d0-53f522188f3d"
      },
      {
        "position": {
          "x": 256,
          "y": -25
        },
        "size": {
          "width": -1,
          "height": -1
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "TEMPERATURA",
            "fontSize": 11
          },
          "specification": {
            "text": "entry / texto_a_imprimir = 6"
          }
        },
        "id": "63206253-529b-498c-831f-91fbb55f7885",
        "z": 99,
        "parent": "c69f044a-5a5f-49bc-b9d0-53f522188f3d"
      },
      {
        "position": {
          "x": -111,
          "y": -29
        },
        "size": {
          "width": -1,
          "height": -1
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "ATASCO",
            "fontSize": 11
          },
          "specification": {
            "text": "entry / texto_a_imprimir = 5; raise EV_ON_BUZZER\nexit / raise EV_OFF_BUZZER"
          }
        },
        "id": "1f2149b1-b432-4ceb-a79f-5068563418b0",
        "z": 100,
        "parent": "c69f044a-5a5f-49bc-b9d0-53f522188f3d"
      },
      {
        "position": {
          "x": -111,
          "y": -63
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "type": "Entry",
        "entryKind": "Initial",
        "attrs": {},
        "id": "aa3bbee3-1caf-427b-b625-e814d0bb65a4",
        "z": 101,
        "parent": "c69f044a-5a5f-49bc-b9d0-53f522188f3d",
        "embeds": [
          "b7a45e57-f7e7-430f-b7bf-3f4e2213ef86"
        ]
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": -111,
          "y": -48
        },
        "attrs": {
          "label": {
            "refX": "50%",
            "textAnchor": "middle",
            "refY": "50%",
            "textVerticalAnchor": "middle"
          }
        },
        "id": "b7a45e57-f7e7-430f-b7bf-3f4e2213ef86",
        "z": 102,
        "parent": "aa3bbee3-1caf-427b-b625-e814d0bb65a4"
      },
      {
        "position": {
          "x": -153,
          "y": -788
        },
        "size": {
          "width": 1395,
          "height": 516
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "SET_UP",
            "fontSize": 11
          },
          "specification": {
            "text": "entry / raise EV_OFF_LED; texto_a_imprimir = 4"
          }
        },
        "id": "3585db34-dc6a-43b6-a3fa-d7e5427acd6e",
        "z": 123,
        "embeds": [
          "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
        ]
      },
      {
        "position": {
          "x": -150,
          "y": -743
        },
        "size": {
          "width": 1389,
          "height": 468
        },
        "type": "Region",
        "attrs": {
          "priority": {
            "text": 1
          }
        },
        "id": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be",
        "z": 124,
        "embeds": [
          "06bf3cc6-7a76-43ce-9622-7ef66e097448",
          "eb3eee22-2884-41d1-879d-866cc02409f8",
          "606ccfa4-0095-464f-94c0-6928d5e65dc2",
          "f9bfdd32-5f32-4269-8ec7-d2750572e6f8",
          "43740e60-dfce-4e09-b5f1-793e40c22785",
          "f6b9d285-266c-4f4f-8599-5e3b6a8f0249",
          "c8990bf0-038c-445e-9d12-06f17af21c38",
          "40e4f905-54c9-4edf-8d80-d1c8a1c0ab8b",
          "6401ed66-4609-4174-959e-0de7bfedad40",
          "3feca282-4991-4182-aa63-277ce67d28b9",
          "0c3628b6-7b9f-4987-b4e0-c1eb502248e9",
          "99b7a2fa-32f2-4257-92ce-33e3a6fdf938",
          "22faae94-7076-4dfa-8800-cf65a6348e36",
          "221f8cf9-68b2-4a73-8553-f4a7c08534ea",
          "69c2ff63-79ed-4fde-b44b-f1c550d9a8a8",
          "dee94bff-0478-4347-bc98-c8e95a448890",
          "5361c8d1-f823-4592-8b77-dddbf38542b1",
          "e0eec02e-441e-4264-874e-d8e1251d7112",
          "09732480-3a6d-4d62-9d8a-bad3723ec598",
          "02b45771-889a-4a57-9477-7e8f1385c933",
          "8c959174-2261-4eff-b8e7-2b51c85461d5",
          "817a29bc-c996-4403-be1c-52b0761444d0",
          "ceb444c6-6df9-4d79-8b11-77cbcc458472",
          "1fde77ad-e990-4832-9c06-dd8d07f6e194"
        ],
        "parent": "3585db34-dc6a-43b6-a3fa-d7e5427acd6e"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "ceb444c6-6df9-4d79-8b11-77cbcc458472"
        },
        "target": {
          "id": "02b45771-889a-4a57-9477-7e8f1385c933",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "79.39%",
              "dy": "33.333%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "/ p2_stock = (p2_stock + 1) % 11"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "06bf3cc6-7a76-43ce-9622-7ef66e097448",
        "z": 125,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": 1031,
            "y": -686
          }
        ],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "02b45771-889a-4a57-9477-7e8f1385c933"
        },
        "target": {
          "id": "1fde77ad-e990-4832-9c06-dd8d07f6e194"
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_NEXT"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "eb3eee22-2884-41d1-879d-866cc02409f8",
        "z": 126,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "1fde77ad-e990-4832-9c06-dd8d07f6e194"
        },
        "target": {
          "id": "817a29bc-c996-4403-be1c-52b0761444d0"
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "[param_idx == 0]"
              }
            },
            "position": {
              "distance": 1,
              "offset": 21.58800717354395,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "606ccfa4-0095-464f-94c0-6928d5e65dc2",
        "z": 127,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": 963,
            "y": -362
          }
        ],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "1fde77ad-e990-4832-9c06-dd8d07f6e194"
        },
        "target": {
          "id": "ceb444c6-6df9-4d79-8b11-77cbcc458472"
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "f9bfdd32-5f32-4269-8ec7-d2750572e6f8",
        "z": 128,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": 1135,
            "y": -484.47
          }
        ],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "817a29bc-c996-4403-be1c-52b0761444d0"
        },
        "target": {
          "id": "02b45771-889a-4a57-9477-7e8f1385c933",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "70.111%",
              "dy": "100%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "/ p2_precio = (p2_precio + 50) % 1000"
              }
            },
            "position": {
              "distance": 0.8836047997502285,
              "offset": -30.976776123046875,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "43740e60-dfce-4e09-b5f1-793e40c22785",
        "z": 129,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": 1016,
            "y": -396
          }
        ],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "ceb444c6-6df9-4d79-8b11-77cbcc458472"
        },
        "target": {
          "id": "02b45771-889a-4a57-9477-7e8f1385c933",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "67.958%",
              "dy": "96.667%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": " [prod_idx == 0] / p0_stock = (p0_stock + 1) % 11"
              }
            },
            "position": {
              "distance": 0.4583944273834532,
              "offset": -14,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "f6b9d285-266c-4f4f-8599-5e3b6a8f0249",
        "z": 130,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": 1130,
            "y": -723
          }
        ],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "ceb444c6-6df9-4d79-8b11-77cbcc458472"
        },
        "target": {
          "id": "02b45771-889a-4a57-9477-7e8f1385c933",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "85.106%",
              "dy": "31.667%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "[prod_idx == 1] / p1_stock = (p1_stock + 1) % 11"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "c8990bf0-038c-445e-9d12-06f17af21c38",
        "z": 131,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": 1103,
            "y": -657
          }
        ],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "817a29bc-c996-4403-be1c-52b0761444d0"
        },
        "target": {
          "id": "02b45771-889a-4a57-9477-7e8f1385c933",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "48.269%",
              "dy": "93.333%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "[prod_idx == 1] / p1_precio = (p1_precio + 50) % 1000"
              }
            },
            "position": {
              "distance": 0.7196410672318588,
              "offset": -65.38672883401422,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "40e4f905-54c9-4edf-8d80-d1c8a1c0ab8b",
        "z": 132,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "817a29bc-c996-4403-be1c-52b0761444d0"
        },
        "target": {
          "id": "02b45771-889a-4a57-9477-7e8f1385c933",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "7.621%",
              "dy": "90%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "[prod_idx == 0] / p0_precio = (p0_precio + 50) % 1000"
              }
            },
            "position": {
              "distance": 0.623513554499622,
              "offset": -123.39024680468658,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "6401ed66-4609-4174-959e-0de7bfedad40",
        "z": 133,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "09732480-3a6d-4d62-9d8a-bad3723ec598"
        },
        "target": {
          "id": "8c959174-2261-4eff-b8e7-2b51c85461d5",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "98.081%",
              "dy": "71.667%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_ESC"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "3feca282-4991-4182-aa63-277ce67d28b9",
        "z": 134,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "5361c8d1-f823-4592-8b77-dddbf38542b1"
        },
        "target": {
          "id": "8c959174-2261-4eff-b8e7-2b51c85461d5",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "6.687%",
              "dy": "35%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_ENTER"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "0c3628b6-7b9f-4987-b4e0-c1eb502248e9",
        "z": 135,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "8c959174-2261-4eff-b8e7-2b51c85461d5"
        },
        "target": {
          "id": "09732480-3a6d-4d62-9d8a-bad3723ec598",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "7.877%",
              "dy": "23.333%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_ENTER"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "99b7a2fa-32f2-4257-92ce-33e3a6fdf938",
        "z": 136,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "8c959174-2261-4eff-b8e7-2b51c85461d5"
        },
        "target": {
          "id": "5361c8d1-f823-4592-8b77-dddbf38542b1",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "96.945%",
              "dy": "78.333%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_ESC"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "22faae94-7076-4dfa-8800-cf65a6348e36",
        "z": 137,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "09732480-3a6d-4d62-9d8a-bad3723ec598"
        },
        "target": {
          "id": "02b45771-889a-4a57-9477-7e8f1385c933",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "7.565%",
              "dy": "23.333%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_ENTER"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "221f8cf9-68b2-4a73-8553-f4a7c08534ea",
        "z": 138,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "02b45771-889a-4a57-9477-7e8f1385c933"
        },
        "target": {
          "id": "09732480-3a6d-4d62-9d8a-bad3723ec598",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "92.418%",
              "dy": "81.667%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_ESC"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "69c2ff63-79ed-4fde-b44b-f1c550d9a8a8",
        "z": 139,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "e0eec02e-441e-4264-874e-d8e1251d7112"
        },
        "target": {
          "id": "5361c8d1-f823-4592-8b77-dddbf38542b1",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "47.591%",
              "dy": "10%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "dee94bff-0478-4347-bc98-c8e95a448890",
        "z": 140,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "position": {
          "x": -85,
          "y": -667
        },
        "size": {
          "width": -1,
          "height": -1
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "St_Main",
            "fontSize": 11
          },
          "specification": {
            "text": "entry/ prod_idx=0"
          }
        },
        "id": "5361c8d1-f823-4592-8b77-dddbf38542b1",
        "z": 141,
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "position": {
          "x": -81,
          "y": -703
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "type": "Entry",
        "entryKind": "Initial",
        "attrs": {},
        "id": "e0eec02e-441e-4264-874e-d8e1251d7112",
        "z": 142,
        "embeds": [
          "51b6bf89-28d8-4139-875d-0c41f17b5840"
        ],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": -81,
          "y": -688
        },
        "attrs": {
          "label": {
            "refX": 15,
            "textAnchor": "end",
            "refY": 15,
            "textVerticalAnchor": "bottom"
          }
        },
        "id": "51b6bf89-28d8-4139-875d-0c41f17b5840",
        "z": 143,
        "parent": "e0eec02e-441e-4264-874e-d8e1251d7112"
      },
      {
        "position": {
          "x": 407.439453125,
          "y": -669
        },
        "size": {
          "height": 60,
          "width": 154
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "St_Menu_2",
            "fontSize": 11
          }
        },
        "id": "09732480-3a6d-4d62-9d8a-bad3723ec598",
        "z": 144,
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be",
        "embeds": [
          "36b179c0-9bbf-479b-a6f6-7c5876b383fa"
        ]
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "09732480-3a6d-4d62-9d8a-bad3723ec598",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "9.977%",
              "dy": "96.667%",
              "rotate": true
            }
          },
          "priority": true
        },
        "target": {
          "id": "09732480-3a6d-4d62-9d8a-bad3723ec598",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "86.642%",
              "dy": "100%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_NEXT/param_idx = (param_idx + 1) % 2"
              }
            },
            "position": {
              "distance": 0.4979307273900082,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "36b179c0-9bbf-479b-a6f6-7c5876b383fa",
        "z": 145,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": 451,
            "y": -701
          }
        ],
        "parent": "09732480-3a6d-4d62-9d8a-bad3723ec598"
      },
      {
        "position": {
          "x": 639,
          "y": -588
        },
        "size": {
          "width": 271,
          "height": 60
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "St_Menu_3",
            "fontSize": 11
          }
        },
        "id": "02b45771-889a-4a57-9477-7e8f1385c933",
        "z": 146,
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "position": {
          "x": 129,
          "y": -668
        },
        "size": {
          "height": 60,
          "width": 162
        },
        "type": "State",
        "attrs": {
          "name": {
            "text": "St_Menu_1",
            "fontSize": 11
          }
        },
        "id": "8c959174-2261-4eff-b8e7-2b51c85461d5",
        "z": 147,
        "embeds": [
          "7f701f52-c37e-4eb8-add8-1181ba2b4454"
        ],
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "8c959174-2261-4eff-b8e7-2b51c85461d5"
        },
        "target": {
          "id": "8c959174-2261-4eff-b8e7-2b51c85461d5",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "90.052%",
              "dy": "98.333%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_NEXT/prod_idx = (prod_idx + 1) % 3"
              }
            },
            "position": {
              "distance": 0.5155069814270368,
              "offset": 16,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "7f701f52-c37e-4eb8-add8-1181ba2b4454",
        "z": 148,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": 133,
            "y": -577
          }
        ],
        "parent": "8c959174-2261-4eff-b8e7-2b51c85461d5"
      },
      {
        "position": {
          "x": 909,
          "y": -370
        },
        "size": {
          "width": 15,
          "height": 15
        },
        "type": "Choice",
        "attrs": {},
        "id": "817a29bc-c996-4403-be1c-52b0761444d0",
        "z": 149,
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "position": {
          "x": 1203,
          "y": -545
        },
        "size": {
          "width": 15,
          "height": 15
        },
        "type": "Choice",
        "attrs": {},
        "id": "ceb444c6-6df9-4d79-8b11-77cbcc458472",
        "z": 150,
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "position": {
          "x": 1084,
          "y": -492
        },
        "size": {
          "width": 15,
          "height": 15
        },
        "type": "Choice",
        "attrs": {},
        "id": "1fde77ad-e990-4832-9c06-dd8d07f6e194",
        "z": 151,
        "parent": "42ec99cf-70bc-44ed-bdf3-28eed3eb84be"
      },
      {
        "position": {
          "x": -1552,
          "y": -444
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "type": "Entry",
        "entryKind": "Initial",
        "attrs": {},
        "id": "555715d9-97cd-4c15-adeb-1f1e60fb778a",
        "z": 163,
        "embeds": [
          "7de562aa-a5f7-4559-8973-1e93ffef2e02"
        ]
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": -1552,
          "y": -429
        },
        "attrs": {
          "label": {
            "refX": "50%",
            "textAnchor": "middle",
            "refY": "50%",
            "textVerticalAnchor": "middle"
          }
        },
        "id": "7de562aa-a5f7-4559-8973-1e93ffef2e02",
        "z": 164,
        "parent": "555715d9-97cd-4c15-adeb-1f1e60fb778a"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "555715d9-97cd-4c15-adeb-1f1e60fb778a"
        },
        "target": {
          "id": "b907b8c2-5dd0-4964-8c42-0947d1d1110d",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "48.675%",
              "dy": "4.219%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": " / raise eeprom_read"
              }
            },
            "position": {
              "distance": 0.4669732441471569,
              "offset": -20.000006103515602,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "c0c7c7d5-1094-4911-96c6-37b22f9b4256",
        "z": 165,
        "router": {
          "name": "orthogonal"
        },
        "vertices": []
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "002b3213-2b67-4e93-8169-4e8c6f6f5a5a"
        },
        "target": {
          "id": "5361c8d1-f823-4592-8b77-dddbf38542b1",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "10.576%",
              "dy": "20%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_SETUP"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "50f2c925-86ae-4ba2-997c-a95e67db9a2a",
        "z": 183,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": -441,
            "y": -655
          }
        ]
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "63206253-529b-498c-831f-91fbb55f7885"
        },
        "target": {
          "id": "002b3213-2b67-4e93-8169-4e8c6f6f5a5a",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "2.79%",
              "dy": "35%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "[temperatura <= TEMP_MAX - 2]"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "e7056501-f182-44bc-90a0-529fd4f34f73",
        "z": 187,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": -1483,
            "y": 80
          }
        ]
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "646e70e7-2be4-4a03-9df3-43da1ad21984"
        },
        "target": {
          "id": "1f2149b1-b432-4ceb-a79f-5068563418b0",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "22.969%",
              "dy": "45%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "after 15 s"
              }
            },
            "position": {
              "distance": 0.5900126299957811,
              "offset": -14,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "94312b89-0472-40f8-8e9f-491b05a06bcf",
        "z": 189,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": -752,
            "y": -45
          }
        ]
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "1f2149b1-b432-4ceb-a79f-5068563418b0"
        },
        "target": {
          "id": "002b3213-2b67-4e93-8169-4e8c6f6f5a5a",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "3.587%",
              "dy": "63.333%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_ESC "
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "92eae09c-434d-4149-97ae-4a711dbe6951",
        "z": 189,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": -1082,
            "y": 19
          },
          {
            "x": -1457,
            "y": -21
          }
        ]
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "3585db34-dc6a-43b6-a3fa-d7e5427acd6e",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "0.129%",
              "dy": "33.915%",
              "rotate": true
            }
          },
          "priority": true
        },
        "target": {
          "id": "002b3213-2b67-4e93-8169-4e8c6f6f5a5a",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "83.294%",
              "dy": "20%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "EV_SYS_NORMAL / raise eeprom_write"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "997e39ee-3de3-40f7-864d-96f9a2ee02b5",
        "z": 193,
        "router": {
          "name": "orthogonal"
        },
        "vertices": []
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "002b3213-2b67-4e93-8169-4e8c6f6f5a5a",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "96.662%",
              "dy": "1.667%",
              "rotate": true
            }
          },
          "priority": true
        },
        "target": {
          "id": "63206253-529b-498c-831f-91fbb55f7885",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "39.145%",
              "dy": "1.667%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "[temperatura > TEMP_MAX]"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "26c2b16c-f39b-4159-9437-37196b7b8957",
        "z": 194,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [
          {
            "x": -270,
            "y": -507
          },
          {
            "x": -194,
            "y": -299
          },
          {
            "x": 61,
            "y": -197
          }
        ]
      },
      {
        "position": {
          "x": -1304,
          "y": -384
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "type": "Entry",
        "entryKind": "Initial",
        "attrs": {},
        "id": "35ac954e-c399-4bce-91a3-ddf0ad4ebba2",
        "z": 195,
        "embeds": [
          "52031d9a-cab0-4261-91e8-254adabb08a8"
        ],
        "parent": "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": -1304,
          "y": -369
        },
        "attrs": {
          "label": {
            "refX": "50%",
            "textAnchor": "middle",
            "refY": "50%",
            "textVerticalAnchor": "middle"
          }
        },
        "id": "52031d9a-cab0-4261-91e8-254adabb08a8",
        "z": 196,
        "parent": "35ac954e-c399-4bce-91a3-ddf0ad4ebba2"
      },
      {
        "type": "Transition",
        "attrs": {},
        "source": {
          "id": "35ac954e-c399-4bce-91a3-ddf0ad4ebba2"
        },
        "target": {
          "id": "002b3213-2b67-4e93-8169-4e8c6f6f5a5a",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": "51.429%",
              "dy": "6.78%",
              "rotate": true
            }
          },
          "priority": true
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "4d02c6a1-2844-4c75-8ba6-f372190f699d",
        "z": 197,
        "router": {
          "name": "orthogonal"
        },
        "vertices": [],
        "parent": "3cd66b33-3c9b-4f04-babf-c466f5974ccc"
      }
    ]
  },
  "genModel": {
    "generator": {
      "type": "create::c",
      "features": {
        "Outlet": {
          "targetProject": "",
          "targetFolder": "",
          "libraryTargetFolder": "",
          "skipLibraryFiles": "",
          "apiTargetFolder": ""
        },
        "LicenseHeader": {
          "licenseText": ""
        },
        "FunctionInlining": {
          "inlineReactions": false,
          "inlineEntryActions": false,
          "inlineExitActions": false,
          "inlineEnterSequences": false,
          "inlineExitSequences": false,
          "inlineChoices": false,
          "inlineEnterRegion": false,
          "inlineExitRegion": false,
          "inlineEntries": false
        },
        "OutEventAPI": {
          "observables": false,
          "getters": false
        },
        "IdentifierSettings": {
          "moduleName": "SystemStatechart",
          "statemachinePrefix": "systemStatechart",
          "separator": "_",
          "headerFilenameExtension": "h",
          "sourceFilenameExtension": "c"
        },
        "Tracing": {
          "enterState": false,
          "exitState": false,
          "generic": false
        },
        "Includes": {
          "useRelativePaths": false,
          "generateAllSpecifiedIncludes": false
        },
        "GeneratorOptions": {
          "userAllocatedQueue": false,
          "metaSource": false
        },
        "GeneralFeatures": {
          "timerService": false,
          "timerServiceTimeType": ""
        },
        "Debug": {
          "dumpSexec": false
        }
      }
    }
  }
}