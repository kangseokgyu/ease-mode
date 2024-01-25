# ease-mode

모드를 변경하고 변경된 모드를 확인하기 위해 만들었습니다.

## 정의하기

`defval`을 넣어야 사용할 수 있습니다.
`mutex`를 사용하려면 `mode_mt`, `mutex`를 사용하지 않으려면 `mode_st`를 사용합니다.

## Example

```C++
enum class mode {
  mode_1,
  mode_2,

  defval = mode1,
};

ease::mode_st<mode> m;

m.change(mode::mode_2);

auto res = m.check();
if (res.first) {
  // change mode  
}
```
