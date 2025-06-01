package com.byak.currencyconverter.model;

import lombok.Data;

@Data
public class CurrencyRate {
    private String currency_name;
    private String rate;
    private String rate_for_amount;
}