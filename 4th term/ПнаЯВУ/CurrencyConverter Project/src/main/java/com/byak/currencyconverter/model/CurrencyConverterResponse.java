package com.byak.currencyconverter.model;

import lombok.Data;

import java.util.Map;

@Data
public class CurrencyConverterResponse {
    private String status;
    private String updated_date;
    private String base_currency_code;
    private double amount;
    private String base_currency_name;
    private Map<String, CurrencyRate> rates;
}
