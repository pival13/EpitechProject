#!/bin/python3

import sys
import re
from enum import Enum
from collections import deque

import indicator
import indice_per_indicator

class message_type(Enum):
    PASS = 0
    BUY = 1
    SELL = 2


def check_if_enough(order, game_stacks, value) -> bool:
    if order['currency'] == "USDT_BTC":
        if order['type'] == 1 and game_stacks['USDT'] > 0 and game_stacks['USDT']*order['indicator']/value > 0.000001 and game_stacks['USDT']*order['indicator']/value < game_stacks['USDT']:
            return True
        elif order['type'] == 2 and game_stacks['BTC'] > 0 and game_stacks['BTC']/(1/order['indicator']) > 0.000001:
            return True
        else:
            return False
    elif order['currency'] == "USDT_ETH":
        if order['type'] == 1 and game_stacks['USDT'] > 0 and game_stacks['USDT']*order['indicator']/value > 0.000001 and game_stacks['USDT']*order['indicator']/value < game_stacks['USDT']:
            return True
        elif order['type'] == 2 and game_stacks['ETH'] > 0 and game_stacks['ETH']/(1/order['indicator']) > 0.000001:
            return True
        else:
            return False


def print_error(message):
    sys.stderr.write(message + "\n")
    sys.stderr.flush()

def print_message(message):
    print(message, flush=True)


def buy_sell_message(type: message_type, currencies: str =None, amount: float = None) -> str:
    if type == message_type.BUY:
        return ("buy" + " " + str(currencies) + " " + str(amount))
    elif type == message_type.SELL:
        return ("sell" + " " + str(currencies) + " " +  str(amount))
    else:
        return ("pass")


def update_stacks(stacks:str, game_stacks):
    split_stacks = stacks.split(',')
    game_stacks["BTC"] = float(split_stacks[0].split(':')[1])
    game_stacks["ETH"] = float(split_stacks[1].split(':')[1])
    game_stacks["USDT"] = float(split_stacks[2].split(':')[1])


def money_values_to_array(money_values):
    values_array = []
    array_not_sorted = money_values.split(',')
    for i in range(2, len(array_not_sorted)):
        values_array.append(float(array_not_sorted[i]))
    return values_array


def money_values_to_dict(money_values):
    thisdict = dict(high=None, low=None, open=None, close=None, volume=None)
    array_not_sorted = money_values.split(',')
    thisdict["open"] = float(array_not_sorted[4])
    thisdict["close"] = float(array_not_sorted[5])
    thisdict["high"] = float(array_not_sorted[2])
    thisdict["low"] = float(array_not_sorted[3])
    return thisdict


def list_dict_to_list(values, key):
    return [v[key] for v in values]


def main():
    index_debug = 0

    is_action_made:bool
    output_message:str
    game_stacks = dict(BTC=None, ETH=None, USDT=None)
    btc_eth = deque(maxlen=200)
    usdt_eth = deque(maxlen=200)
    usdt_btc = deque(maxlen=200)

    rsi10_eth = deque(maxlen=200)
    rsi18_eth = deque(maxlen=200)
    rsi20_eth = deque(maxlen=200)
    rsi21_eth = deque(maxlen=200)
    rsi25_eth = deque(maxlen=200)
    rsi50_eth = deque(maxlen=200)
    macd_eth = deque(maxlen=2)
    bb20_eth = deque(maxlen=200)
    bb25_eth = deque(maxlen=200)
    bb26_eth = deque(maxlen=200)

    rsi10_btc = deque(maxlen=200)
    rsi18_btc = deque(maxlen=200)
    rsi20_btc = deque(maxlen=200)
    rsi21_btc = deque(maxlen=200)
    rsi25_btc = deque(maxlen=200)
    rsi50_btc = deque(maxlen=200)
    macd_btc = deque(maxlen=2)
    bb20_btc = deque(maxlen=200)
    bb25_btc = deque(maxlen=200)
    bb26_btc = deque(maxlen=200)

    while True:
        is_action_made = False
        output_message = ""

        s = sys.stdin.readline()
        s_str = str(s)
        if s_str.startswith("settings "):
            settings = s_str[len("settings "):]
            if settings.startswith("timebank"):
                timebank = float(settings[len("timebank "):])
        elif s_str.startswith("update game next_candles"):
            update_game = s_str[len("update game next_candles "):]
            values_array = update_game.split(';')
            btc_eth.append(money_values_to_dict(values_array[0]))
            usdt_eth.append(money_values_to_dict(values_array[1]))
            usdt_btc.append(money_values_to_dict(values_array[2]))
            #Etherium indicators
            rsi10_eth += [indicator.relativeStrengthIndex(list_dict_to_list(usdt_eth, "close"), 10)]
            rsi18_eth += [indicator.relativeStrengthIndex(list_dict_to_list(usdt_eth, "close"), 18)]
            rsi20_eth += [indicator.relativeStrengthIndex(list_dict_to_list(usdt_eth, "close"), 20)]
            rsi50_eth += [indicator.relativeStrengthIndex(list_dict_to_list(usdt_eth, "close"), 50)]
            macd_eth += [indicator.movingAverageConvDiv(list_dict_to_list(usdt_eth, "close"), 12, 26, 9)]
            bb20_eth += [indicator.bollingerBands(list_dict_to_list(usdt_eth, "close"), 20)]
            bb26_eth += [indicator.bollingerBands(list_dict_to_list(usdt_eth, "close"), 26)]
            #Bitcoin indicators
            rsi10_btc += [indicator.relativeStrengthIndex(list_dict_to_list(usdt_btc, "close"), 10)]
            rsi18_btc += [indicator.relativeStrengthIndex(list_dict_to_list(usdt_btc, "close"), 18)]
            rsi20_btc += [indicator.relativeStrengthIndex(list_dict_to_list(usdt_btc, "close"), 20)]
            rsi50_btc += [indicator.relativeStrengthIndex(list_dict_to_list(usdt_btc, "close"), 50)]
            macd_btc += [indicator.movingAverageConvDiv(list_dict_to_list(usdt_btc, "close"), 12, 26, 9)]
            bb20_btc += [indicator.bollingerBands(list_dict_to_list(usdt_btc, "close"), 20)]
            bb26_btc += [indicator.bollingerBands(list_dict_to_list(usdt_btc, "close"), 26)]
        elif s_str.startswith("update game stacks"):
            stacks = s_str[len("update game stacks "):]
            update_stacks(stacks, game_stacks)
        elif s_str.startswith("action order"):
            #Etherium BUY/SELL ORDERS
          #  eth_order:dict = indice_per_indicator.buy_sell_order(usdt_eth[-1]['close'], rsi18_eth[-1], rsi18_eth[-2], bb26_eth, "USDT_ETH")
          #  print_error(str(eth_order))
          #  if eth_order['type'] != 0 and check_if_enough(eth_order, game_stacks, usdt_eth[-1]['close']) == True:
          #      print_error("toto1")
          #      output_message += buy_sell_message(message_type.BUY if eth_order['type'] == 1 else message_type.SELL, eth_order['currency'], game_stacks['USDT']*eth_order['indicator']/usdt_eth[-1]['close'] if eth_order['type'] == 1 else game_stacks['ETH']/(1/eth_order['indicator']))
          #      if eth_order['type'] == 1:
          #          game_stacks['USDT'] -= game_stacks['USDT']*eth_order['indicator']
          #      else:
          #          game_stacks['USDT'] += game_stacks['ETH']/(1/eth_order['indicator']) / usdt_eth[-1]['close']
          #      is_action_made = True
          #  #if macd_eth[1]['Histogram'] <= 0 and macd_eth[0]['Histogram'] > 0 and game_stacks['USDT'] > 0:
          #  #    bought = True
          #  #    output_message += buy_sell_message(message_type.BUY, "USDT_ETH", game_stacks['USDT']*0.4/usdt_eth[-1]['high'])
          #  #elif macd_eth[1]['Histogram'] >= 0 and macd_eth[0]['Histogram'] < 0 and game_stacks['ETH'] > 0:
          #  #    bought = True
          #  #    output_message += buy_sell_message(message_type.SELL, "USDT_ETH", game_stacks['ETH']/2)
          #  
          #  #Bitcoin BUY/SELL ORDERS
          #  btc_order:dict = indice_per_indicator.buy_sell_order(usdt_btc[-1]['close'], rsi18_btc[-1], rsi18_btc[-2], bb26_btc, "USDT_BTC")
          #  print_error(str(btc_order))
          #  if btc_order['type'] != 0 and check_if_enough(btc_order, game_stacks, usdt_btc[-1]['close']) == True:
          #      print_error("toto2")
          #      if is_action_made is True:
          #          output_message += ";"
          #      is_action_made = True
          #      output_message += buy_sell_message(message_type.BUY if btc_order['type'] == 1 else message_type.SELL, btc_order['currency'], game_stacks['USDT']*btc_order['indicator']/usdt_btc[-1]['close'] if btc_order['type'] == 1 else game_stacks['BTC']/(1/btc_order['indicator']))
          #  #if macd_btc[1]['Histogram'] <= 0 and macd_btc[0]['Histogram'] > 0 and game_stacks['USDT'] > 0:
          #  #    if bought is True:
          #  #        output_message += ";"
          #  #    bought = True
          #  #    output_message += buy_sell_message(message_type.BUY, "USDT_BTC", game_stacks['USDT']*0.4/usdt_btc[-1]['high'])
          #  #elif macd_btc[1]['Histogram'] >= 0 and macd_btc[0]['Histogram'] < 0 and game_stacks['BTC'] > 0:
          #  #    if bought is True:
          #  #        output_message += ";"
          #  #    bought = True
          #  #    output_message += buy_sell_message(message_type.SELL, "USDT_BTC", game_stacks['BTC']/2)
          #  #pass if nothing
            todo1 = indice_per_indicator.determine_action_to_do(list_dict_to_list(usdt_btc, "close"), rsi10_btc, rsi20_btc, rsi50_btc, bb20_btc, macd_btc) / 10
            todo2 = indice_per_indicator.determine_action_to_do(list_dict_to_list(usdt_eth, "close"), rsi10_eth, rsi20_eth, rsi50_eth, bb20_eth, macd_eth) / 10
          #  if is_action_made == False:
          #      print_error("PASS")
          #      print_message(buy_sell_message(message_type.PASS))
          #  else:
          #      print_error("MESSAGE : " + output_message)
          #      print_message(output_message)
            msg = []
            money = game_stacks['USDT']
            for currency, indice, value in ([["BTC", todo1, usdt_btc[-1]], ["ETH", todo2, usdt_eth[-1]]] if abs(todo1) > abs(todo2) else [["ETH", todo2, usdt_eth[-1]],["BTC", todo1, usdt_btc[-1]]]):
                if indice < 0 and money*-indice/100/value['high'] > 0:
                    msg += [f"BUY USDT_{currency} {money*-indice/100/value['high']}"]
                    money -= money*-indice/100
                elif todo1 > 0 and game_stacks[currency]*indice/75 > 0:
                    msg += [f"SELL USDT_{currency} {game_stacks[currency]*indice/75}"]
                    money += game_stacks[currency]*indice/75 * value['low']

            print(";".join(msg) if len(msg) > 0 else "PASS", flush=True)
    return

#Utiliser BB (Bollinger Bands)
#Macd peut être utiliser pour déterminer achat/vente optimal (~5j écart)
#RSI sur 10, 20 et 50 jours et BB pour déterminer quantité vente

if __name__ == "__main__":
    main()