package com.byak.currencyconverter.controller;

import com.byak.currencyconverter.model.CurrencyConverterResponse;
import com.byak.currencyconverter.service.CurrencyConverterService;
import lombok.AllArgsConstructor;
import org.springframework.web.bind.annotation.*;

@RestController
@AllArgsConstructor
@RequestMapping("/convert")
public class CurrencyConverterController {
    private CurrencyConverterService currencyConverterService;

    @GetMapping("/{fromCurrency}/{toCurrency}/{amount}")
    public CurrencyConverterResponse convertCurrency(@PathVariable String fromCurrency,
                                                     @PathVariable String toCurrency,
                                                     @PathVariable double amount) {
        return currencyConverterService.convertCurrency(fromCurrency, toCurrency, amount);
    }
}
